#include "BitvectorArrays.h"
#include "BitvectorUFs.h"
#include "Bitvectors.h"
#include "Boolector.h"
#include "SatCore.h"

#include <cstring>
#include <cstdlib>

namespace SMT
{

Boolector::Boolector(SATSolver solver)
  : m_btor(boolector_new()),
    m_result(Solver::Unknown),
    m_sat(new BoolectorSatCore(m_btor)),
    m_bvs(new BoolectorBitvectors(m_btor)),
    m_ufs(NULL),
    m_bvArrays(NULL),
    m_description(),
    m_incremental(false),
    m_lastBoolExp(NULL),
    m_lastBoolVal(false),
    m_lastBoolMask(false)
{
    switch (solver) {
    case PicoSAT:
#ifdef PICOSAT
        boolector_set_sat_solver(m_btor, "PicoSAT");
        m_description = "Boolector with PicoSAT";
#else
        throw LLBMCException("No PicoSAT support for Boolector");
#endif
        break;
    case MiniSat:
#ifdef BOOLECTOR_MINISAT
        boolector_set_sat_solver(m_btor, "MiniSat");
        m_description = "Boolector with MiniSat";
#else
        throw LLBMCException("No MiniSat support for Boolector");
#endif
        break;
    case Lingeling:
        boolector_set_sat_solver(m_btor, "Lingeling");
        m_description = "Boolector with Lingeling";
        break;
    default:
        throw LLBMCException("Unknown SAT solver");
    }
    boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);
}

Boolector::~Boolector()
{
    delete m_bvArrays;
    delete m_bvs;
    delete m_sat;

    boolector_delete(m_btor);
}

int Boolector::getNumUnreleasedExps() const
{
    return boolector_get_refs(m_btor);
}

bool Boolector::hasCapability(Capability cap) const
{
    switch (cap) {
    case CapPushPop:
    case CapTheoryOfHeaps:
    case CapArraySetAndCopy:
    case CapTheoryOfFPs:
    case CapTheoryOfLIA:
    case CapTimeout:
        return false;
    case CapSMTSolving:
    case CapIncrementalSolving:
    case CapAssume:
    case CapTheoryOfArrays:
    case CapTheoryOfBitvectors:
    case CapTheoryOfUninterpretedFunctions:
        return true;
    default:
        return false;
    }
}

SatCore *Boolector::getSatCore()
{
    return m_sat;
}

TheoryOfBitvectors *Boolector::getTheoryOfBitvectors()
{
    return m_bvs;
}

BitvectorTheoryOfArrays *Boolector::getBitvectorTheoryOfArrays()
{
    if (m_bvArrays == NULL) {
        m_bvArrays = new BoolectorBVArrays(m_btor);
    }
    return m_bvArrays;
}

BitvectorTheoryOfUFs *Boolector::getBitvectorTheoryOfUFs()
{
    if (m_ufs == NULL) {
        m_ufs = new BoolectorBVUFs(m_btor);
    }
    return m_ufs;
}

bool Boolector::hasModel()
{
    return m_result == Solver::Satisfiable;
}

Model *Boolector::getModel()
{
    if (m_result == Solver::Satisfiable) {
        return this;
    } else {
        return NULL;
    }
}

void Boolector::valuateBoolean(BoolExp *exp) const
{
    if (exp == m_lastBoolExp) {
        return;
    }

    m_lastBoolExp = exp;

    const char *string = boolector_bv_assignment(m_btor, toBtor(exp));

    if (string == NULL) {
        m_lastBoolVal = false;
        m_lastBoolMask = false;
    } else if (string[0] == '1') {
        m_lastBoolVal = true;
        m_lastBoolMask = true;
    } else if (string[0] == '0') {
        m_lastBoolVal = false;
        m_lastBoolMask = true;
    } else {
        m_lastBoolVal = false;
        m_lastBoolMask = false;
    }

    boolector_free_bv_assignment(m_btor, string);
}

bool Boolector::getBoolean(BoolExp *exp) const
{
    valuateBoolean(exp);
    return m_lastBoolVal;
}

bool Boolector::getBooleanMask(BoolExp *exp) const
{
    valuateBoolean(exp);
    return m_lastBoolMask;
}

void Boolector::parseBitvector(Bitvector &bv, const char *str) const
{
    unsigned int width = bv.getWidth();
    unsigned int length = static_cast<unsigned int>(strlen(str));

    if (width != length) {
        bv = Bitvector();
        throw LLBMCException("Unexpected width of bitvector model!");
    }

    for (unsigned int i = 0; i < width; ++i) {
        char c = str[i];
        switch (c) {
        case '0':
            bv.setBit(width-i-1, 0);
            break;
        case '1':
            bv.setBit(width-i-1, 1);
            break;
        case 'x':
        case 'X':
            bv = Bitvector();
            break;
        case '\0':
            bv = Bitvector();
            throw LLBMCException("Unexpected end of bitvector model!");
        default:
            bv = Bitvector();
            throw LLBMCException("Unexpected character in bitvector model!");
        }
    }
}

void Boolector::parseBitvectorTreatXAsZero(Bitvector &bv, const char *str) const
{
    unsigned int width = bv.getWidth();
    unsigned int length = static_cast<unsigned int>(strlen(str));

    if (width != length) {
        bv = Bitvector();
        throw LLBMCException("Unexpected width of bitvector model!");
    }

    for (unsigned int i = 0; i < width; ++i) {
        char c = str[i];
        switch (c) {
        case '0':
        case 'x':
        case 'X':
            bv.setBit(width-i-1, 0);
            break;
        case '1':
            bv.setBit(width-i-1, 1);
            break;
        default:
            bv = Bitvector();
            throw LLBMCException("Unexpected character in bitvector model!");
        }
    }
}

void Boolector::parseBitvector(Bitvector &bv, const char *str, bool treatXAsZero) const
{
    if (treatXAsZero) {
        parseBitvectorTreatXAsZero(bv, str);
    } else {
        parseBitvector(bv, str);
    }
}

const Bitvector *Boolector::getBitvector(BVExp *exp, bool treatXAsZero) const
{
    const char *str = boolector_bv_assignment(m_btor, toBtor(exp));

    Bitvector *res = new Bitvector(0, static_cast<unsigned int>(strlen(str)));
    parseBitvector(*res, str, treatXAsZero);
    boolector_free_bv_assignment(m_btor, str);

    if (res->isValid()) {
        return res;
    } else {
        delete res;
        return NULL;
    }
}

const Bitvector *Boolector::getBitvector(BVExp *exp) const
{
    return getBitvector(exp, true);
}

const BVArray *Boolector::getBVArray(AExp *exp, bool treatXAsZero) const
{
    unsigned int indexWidth;
    unsigned int valueWidth = static_cast<unsigned int>(boolector_get_width(m_btor, toBtor(exp)));

    BVArray *ret = BVArray::create(Bitvector(0, valueWidth));

    char **indices = NULL;
    char **values = NULL;
    int size;

    boolector_array_assignment(m_btor, toBtor(exp), &indices, &values, &size);

    if (size == 0) {
        return ret;
    }

    indexWidth = static_cast<unsigned int>(boolector_get_index_width(m_btor, toBtor(exp)));

    Bitvector index(0, indexWidth);
    Bitvector value(0, valueWidth);

    // convert Bitvectors
    for (int i = 0; i != size; ++i) {
        parseBitvector(index, indices[i], treatXAsZero);
        parseBitvector(value, values[i], treatXAsZero);

        if (index.isValid() && value.isValid()) {
            ret->insert(index, value);
        }
    }

    boolector_free_array_assignment(m_btor, indices, values, size);

    return ret;
}

const BVArray *Boolector::getBVArray(AExp *exp) const
{
    return getBVArray(exp, true);
}

namespace
{
std::string filter_blanks(const char *str)
{
    std::string res;
    while (*str != 0) {
        if (*str != ' ') {
            res.append(1, *str);
        }
        ++str;
    }
    return res;
}

}

const BVArray *Boolector::getBVUF(UFExp *exp, bool treatXAsZero) const
{
    unsigned int indexWidth;
    unsigned int valueWidth = static_cast<unsigned int>(boolector_get_width(m_btor, toBtor(exp)));

    BVArray *ret = BVArray::create(Bitvector(0, valueWidth));

    char **indices = NULL;
    char **values = NULL;
    int size;

    boolector_uf_assignment(m_btor, toBtor(exp), &indices, &values, &size);

    if (size == 0) {
        return ret;
    }

    indexWidth = filter_blanks(indices[0]).length();

    Bitvector index(0, indexWidth);
    Bitvector value(0, valueWidth);

    // convert Bitvectors
    for (int i = 0; i != size; ++i) {
        parseBitvector(index, filter_blanks(indices[i]).c_str(), treatXAsZero);
        parseBitvector(value, values[i], treatXAsZero);

        if (index.isValid() && value.isValid()) {
            ret->insert(index, value);
        }
    }

    boolector_free_uf_assignment(m_btor, indices, values, size);

    return ret;
}

const BVArray *Boolector::getBVUF(UFExp *exp) const
{
    return getBVUF(exp, true);
}

void Boolector::assertConstraint(BoolExp *exp)
{
    boolector_assert(m_btor, toBtor(exp));
}

void Boolector::assume(BoolExp *exp)
{
    boolector_assume(m_btor, toBtor(exp));
}

void Boolector::solve()
{
    // call boolector sat and store result
    int result = boolector_sat(m_btor);

    if (result == BOOLECTOR_UNSAT) {
        m_result = Solver::Unsatisfiable;
    } else if (result == BOOLECTOR_SAT) {
        m_result = Solver::Satisfiable;
    } else {
        m_result = Solver::Unknown;
    }
}

Solver::Result Boolector::getResult() const
{
    return m_result;
}

const std::string &Boolector::getDescription() const
{
    return m_description;
}

void Boolector::enableIncrementalSolving()
{
    boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
}

Solver *createBoolectorLingelingSolver()
{
    return new Boolector(Boolector::Lingeling);
}

Solver *createBoolectorPicoSATSolver()
{
    return new Boolector(Boolector::PicoSAT);
}

Solver *createBoolectorMiniSatSolver()
{
    return new Boolector(Boolector::MiniSat);
}

}

