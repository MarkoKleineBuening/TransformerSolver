#include <llbmc/Util/LLBMCException.h>

#include "LambdarizedToASC.h"
#include "Common.h"

#include "BitvectorArrays.h"

#include <sstream>

#include <iostream>

namespace SMT
{

bool BoolectorLambdarizedToASC::hasCapability(Capability cap) const
{
    if (cap == CapArraySetAndCopy) {
        return true;
    } else {
        return Boolector::hasCapability(cap);
    }
}

class BoolectorLambdarizedToASC::BitvectorArraysWithLambdarizedToASC : public BoolectorBVArrays
{
public:
    BitvectorArraysWithLambdarizedToASC(Btor *p)
      : BoolectorBVArrays(p),
        m_btor(p)
    {}

    ~BitvectorArraysWithLambdarizedToASC()
    {}

    AExp *memcpy(AExp*, BVExp*, AExp*, BVExp*, BVExp*);
    AExp *memset(AExp*, BVExp*, BVExp*, BVExp*);

private:
    BitvectorArraysWithLambdarizedToASC(const BitvectorArraysWithLambdarizedToASC&);
    BitvectorArraysWithLambdarizedToASC &operator=(const BitvectorArraysWithLambdarizedToASC&);

    Btor *m_btor;
};

AExp *BoolectorLambdarizedToASC::BitvectorArraysWithLambdarizedToASC::memcpy(AExp *dstA, BVExp *dstI, AExp *srcA, BVExp *srcI, BVExp *size)
{
    // a
    BoolectorNode *a = toBtor(dstA);

    // p
    BoolectorNode *p = toBtor(dstI);

    // b
    BoolectorNode *b = toBtor(srcA);

    // q
    BoolectorNode *q = toBtor(srcI);

    // s
    BoolectorNode *s = toBtor(size);

    // r
    BoolectorSort bvSort = boolector_bitvec_sort(m_btor, boolector_get_width(m_btor, toBtor(srcI)));
    BoolectorNode *r = boolector_param(m_btor, bvSort, "r");

    BoolectorNode *cond1 = boolector_ulte(m_btor, p, r);
    BoolectorNode *p_plus_s = boolector_add(m_btor, p, s);
    BoolectorNode *cond2 = boolector_ult(m_btor, r, p_plus_s);
    BoolectorNode *cond = boolector_and(m_btor, cond1, cond2);

    boolector_release(m_btor, cond2);
    boolector_release(m_btor, p_plus_s);
    boolector_release(m_btor, cond1);

    BoolectorNode *read1 = boolector_read(m_btor, a, r);

    BoolectorNode *r_minus_p = boolector_sub(m_btor, r, p);
    BoolectorNode *qPlusRMinusP = boolector_add(m_btor, q, r_minus_p);
    BoolectorNode *read2 = boolector_read(m_btor, b, qPlusRMinusP);

    BoolectorNode *body = boolector_cond(m_btor, cond, read2, read1);

    boolector_release(m_btor, read2);
    boolector_release(m_btor, qPlusRMinusP);
    boolector_release(m_btor, r_minus_p);
    boolector_release(m_btor, read1);

    // return lambda term
    BoolectorNode *res = boolector_fun(m_btor, &r, 1, body);
    return toAExp(res);
}

AExp *BoolectorLambdarizedToASC::BitvectorArraysWithLambdarizedToASC::memset(AExp *dstA, BVExp *dstI, BVExp *value, BVExp *size)
{
    // a
    BoolectorNode *a = toBtor(dstA);

    // p
    BoolectorNode *p = toBtor(dstI);

    // v
    BoolectorNode *v = toBtor(value);

    // s
    BoolectorNode *s = toBtor(size);

    // r
    BoolectorSort bvSort = boolector_bitvec_sort(m_btor, boolector_get_width(m_btor, toBtor(dstI)));
    BoolectorNode *r = boolector_param(m_btor, bvSort, "r");

    BoolectorNode *cond1 = boolector_ulte(m_btor, p, r);
    BoolectorNode *p_plus_s = boolector_add(m_btor, p, s);
    BoolectorNode *cond2 = boolector_ult(m_btor, r, p_plus_s);
    BoolectorNode *cond = boolector_and(m_btor, cond1, cond2);

    boolector_release(m_btor, cond2);
    boolector_release(m_btor, p_plus_s);
    boolector_release(m_btor, cond1);

    BoolectorNode *read1 = boolector_read(m_btor, a, r);

    BoolectorNode *body = boolector_cond(m_btor, cond, v, read1);

    boolector_release(m_btor, read1);

    // return lambda term
    BoolectorNode *res = boolector_fun(m_btor, &r, 1, body);
    return toAExp(res);
}

BoolectorLambdarizedToASC::BoolectorLambdarizedToASC(SATSolver solver)
  : Boolector(solver)
{
    if (solver == PicoSAT) {
        m_description = "Boolector with Lambda ToASC and PicoSAT";
    } else if (solver == MiniSat) {
        m_description = "Boolector with LambdaToASC and MiniSat";
    } else {
        m_description = "Boolector with Lambda ToASC and Lingeling";
    }
}

BoolectorLambdarizedToASC::~BoolectorLambdarizedToASC()
{}

BitvectorTheoryOfArrays *BoolectorLambdarizedToASC::getBitvectorTheoryOfArrays()
{
    if (m_bvArrays == NULL) {
        m_bvArrays = new BitvectorArraysWithLambdarizedToASC(m_btor);
    }
    return m_bvArrays;
}

Solver *createBoolectorLambdarizedToASCLingelingSolver()
{
    return new BoolectorLambdarizedToASC(Boolector::Lingeling);
}

Solver *createBoolectorLambdarizedToASCPicoSATSolver()
{
    return new BoolectorLambdarizedToASC(Boolector::PicoSAT);
}

Solver *createBoolectorLambdarizedToASCMiniSatSolver()
{
    return new BoolectorLambdarizedToASC(Boolector::MiniSat);
}

}

