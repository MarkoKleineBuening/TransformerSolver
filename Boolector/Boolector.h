#ifndef SMT_BOOLECTOR_H
#define SMT_BOOLECTOR_H

#include <llbmc/SMT/Solver.h>
#include <llbmc/SMT/Model.h>

#include <string>

struct Btor;

namespace SMT
{

/// \brief Boolector SMT::Solver implementation
///
/// This is an implementation of the Solver interface and a wrapper around
/// the boolector SMT solver (mainly the btor object)
/// \ingroup SMT
class Boolector
  : public Solver,
    public Model
{
public:
    /// \brief Enumeration of the different SAT solver that Boolector can use
    enum SATSolver
    {
        Lingeling,
        PicoSAT,
        MiniSat
    };

    Boolector(SATSolver solver=Lingeling);
    virtual ~Boolector();

    int getNumUnreleasedExps() const;

    virtual bool hasCapability(Capability) const;

    virtual SatCore *getSatCore();
    virtual TheoryOfBitvectors *getTheoryOfBitvectors();
    virtual BitvectorTheoryOfArrays *getBitvectorTheoryOfArrays();
    virtual BitvectorTheoryOfUFs *getBitvectorTheoryOfUFs();

    virtual bool hasModel();
    virtual Model *getModel();

    virtual bool getBoolean(BoolExp*) const;
    virtual bool getBooleanMask(BoolExp*) const;

    virtual const Bitvector *getBitvector(BVExp *) const;

    virtual const BVArray *getBVArray(AExp*) const;

    virtual const BVArray *getBVUF(UFExp*) const;

    virtual void assertConstraint(BoolExp *exp);

    virtual void assume(BoolExp *exp);

    virtual void solve();

    virtual Result getResult() const;

    virtual const std::string &getDescription() const;

    virtual void enableIncrementalSolving();

private:
    Boolector(const Boolector &);
    Boolector &operator=(const Boolector &);

    void valuateBoolean(BoolExp*) const;

    void parseBitvector(Bitvector &bv, const char *str) const;
    void parseBitvectorTreatXAsZero(Bitvector &bv, const char *str) const;
    void parseBitvector(Bitvector &bv, const char *str, bool treatXAsZero) const;
    const Bitvector *getBitvector(BVExp*, bool) const;

    const BVArray *getBVArray(AExp*, bool) const;
    const BVArray *getBVUF(UFExp*, bool) const;

protected:
    Btor *m_btor;

private:
    Result m_result;

    SatCore *m_sat;
    TheoryOfBitvectors *m_bvs;
    BitvectorTheoryOfUFs *m_ufs;

protected:
    BitvectorTheoryOfArrays* m_bvArrays;

    std::string m_description;

private:
    bool m_incremental;

    mutable BoolExp *m_lastBoolExp;
    mutable bool m_lastBoolVal;
    mutable bool m_lastBoolMask;
};

}

#endif

