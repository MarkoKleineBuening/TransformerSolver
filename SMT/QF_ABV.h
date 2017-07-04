#ifndef SMT_QF_ABV_H
#define SMT_QF_ABV_H

#include "SatCore.h"
#include "TheoryOfBitvectors.h"
#include "TheoryOfArrays.h"

namespace SMT
{

/// \brief Collection of support methods for TheoryOfBitvector theory implementations.
///
/// This class implements the part of the TheoryOfBitvectors interface that is
/// not part of the SMTLib specification, but easily implemented on top of the
/// bitvector theory.
/// \note The class is only interesting if you want to implement a new SMT::Solver.
/// \ingroup SMT
class QF_ABV : public SatCore, public TheoryOfBitvectors, public BitvectorTheoryOfArrays
{
public:
    // make sure the base class definitions of these classes also work when using QF_ABV
    using SatCore::release;
    using TheoryOfBitvectors::release;
    using BitvectorTheoryOfArrays::release;
    using TheoryOfBitvectors::eq;
    using BitvectorTheoryOfArrays::eq;
    using SatCore::copy;
    using TheoryOfBitvectors::copy;

    BoolExp *bvne(BVExp*, BVExp*);
    BoolExp *bvule(BVExp*, BVExp*);
    BoolExp *bvugt(BVExp*, BVExp*);
    BoolExp *bvuge(BVExp*, BVExp*);
    BoolExp *bvslt(BVExp*, BVExp*);
    BoolExp *bvsle(BVExp*, BVExp*);
    BoolExp *bvsgt(BVExp*, BVExp*);
    BoolExp *bvsge(BVExp*, BVExp*);

    BoolExp *bvuaddo(BVExp*, BVExp*);
    BoolExp *bvusubo(BVExp*, BVExp*);
    BoolExp *bvumulo(BVExp*, BVExp*);
    BoolExp *bvsaddo(BVExp*, BVExp*);
    BoolExp *bvssubo(BVExp*, BVExp*);
    BoolExp *bvsmulo(BVExp*, BVExp*);
    BoolExp *bvsdivo(BVExp*, BVExp*);

    BVExp *uext(BVExp*, unsigned int);
    BVExp *sext(BVExp*, unsigned int);

    BVExp *bvxor(BVExp*, BVExp*);
    BVExp *bvimplies(BVExp*, BVExp*);

    BVExp *bvsub(BVExp*, BVExp*);
    BVExp *bvsdiv(BVExp*, BVExp*);
    BVExp *bvsrem(BVExp*, BVExp*);

    BVExp *bvashr(BVExp*, BVExp*);

private:
    BVExp *bvArithRightShift(BVExp *exp, unsigned int amount, BoolExp *isSigned, unsigned int shiftBits);

};

}

#endif

