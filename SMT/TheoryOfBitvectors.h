#ifndef SMT_THEORY_OF_BITVECTORS_H
#define SMT_THEORY_OF_BITVECTORS_H

#include "SatCore.h"

// llbmc includes
#include <llbmc/Util/Bitvector.h>

namespace SMT
{

/// \class SMT::BVExp
/// \brief Opaque bitvector expression for SMT solvers.
/// \ingroup SMT
class BVExp;

/// \brief Interface for the theory of bitvectors
/// \ingroup SMT
class TheoryOfBitvectors
{
public:
    virtual ~TheoryOfBitvectors()
    {}

    /// Inserts bitvector variable
    virtual BVExp *bitvector(unsigned int width, const std::string &name) = 0;

    /// Copy this bitvector
    virtual BVExp *copy(BVExp*) = 0;

    /// Convert propositional logic expression to a bitvector
    virtual BVExp *bool2bv1(BoolExp*) = 0;

    /// Convert the bitvector to a propositional logic expression
    virtual BoolExp *bv12bool(BVExp*) = 0;

    /// Inserts equality for bitvectors
    virtual BoolExp *eq(BVExp*, BVExp*) = 0;

    //  (concat (_ BitVec i) (_ BitVec j) (_ BitVec m))
    /// Inserts bitvector concat
    virtual BVExp *concat(BVExp*, BVExp*) = 0;

    //  ((_ extract i j) (_ BitVec m) (_ BitVec n))
    /// Inserts bitvector extract
    virtual BVExp *extract(unsigned int i, unsigned int j, BVExp *) = 0;

    // (op1 (_ BitVec m) (_ BitVec m))
    /// Inserts bitvector not
    virtual BVExp *bvnot(BVExp*) = 0;

    /// Inserts bitvector neg
    virtual BVExp *bvneg(BVExp*) = 0;

    // (op2 (_ BitVec m) (_ BitVec m) (_ BitVec m))
    /// Inserts bitvector and
    virtual BVExp *bvand(BVExp*, BVExp*) = 0;
    /// Inserts bitvector or
    virtual BVExp *bvor(BVExp*, BVExp*) = 0;

    /// Inserts bitvector addition
    virtual BVExp *bvadd(BVExp*, BVExp*) = 0;
    /// Inserts bitvector multiplicaton
    virtual BVExp *bvmul(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned division. Div-by-zero yields undefined behavior!
    virtual BVExp *bvudiv(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned remainder. Div-by-zero yields undefined behavior!
    virtual BVExp *bvurem(BVExp*, BVExp*) = 0;
    /// Inserts bitvector shift left. All bits are shifted out if the shift width is big enough.
    virtual BVExp *bvshl(BVExp*, BVExp*) = 0;
    /// Inserts bitvector logical shift right. All bits are shifted out if the shift width is big enough.
    virtual BVExp *bvlshr(BVExp*, BVExp*) = 0;

    // (bvult (_ BitVec m) (_ BitVec m) Bool)
    /// Inserts bitvector unsigned less than
    virtual BoolExp *bvult(BVExp*, BVExp*) = 0;

    // convenience functions not mentioned in the SMTlib theory of bitvectors

    // initializer functions
    /// Inserts bitvector from integer
    virtual BVExp *bv2bv(const Bitvector *bv) = 0;
    /// Inserts zeros bitvector
    virtual BVExp *bvzeros(unsigned int width) = 0;
    /// Inserts ones bitvector
    virtual BVExp *bvones(unsigned int width) = 0;

    // signed unsigned extension functions
    /// Inserts bitvector unsigned extension, second argument is new width
    virtual BVExp *uext(BVExp *, unsigned int newWidth) = 0;
    /// Inserts bitvector signed extension, second argument is new width
    virtual BVExp *sext(BVExp *, unsigned int newWidth) = 0;

    // logic functions
    /// Inserts bitvector not equal
    virtual BoolExp *bvne(BVExp*, BVExp*) = 0;

    /// Inserts bitvector xor
    virtual BVExp *bvxor(BVExp*, BVExp*) = 0;
    /// Inserts bitvector implies
    virtual BVExp *bvimplies(BVExp*, BVExp*) = 0;
    /// Inserts bitvector conditional
    virtual BVExp *bvcond(BoolExp*, BVExp*, BVExp*) = 0;

    // arithmetic functions
    /// Inserts bitvector subtraction
    virtual BVExp *bvsub(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed division. Div-by-zero yields undefined behavior!
    virtual BVExp *bvsdiv(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed remainder. Div-by-zero yields undefined behavior!
    virtual BVExp *bvsrem(BVExp*, BVExp*) = 0;
    /// Inserts bitvector arithmetical right shift. All bits are shifted out if the shift width is big enough.
    virtual BVExp *bvashr(BVExp*, BVExp*) = 0;

    // overflow checks for unsigned bitvector arithmetics
    /// Inserts bitvector unsiged add overflow check
    virtual BoolExp *bvuaddo(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned sub overflow check
    virtual BoolExp *bvusubo(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned mul overflow check
    virtual BoolExp *bvumulo(BVExp*, BVExp*) = 0;

    // overflow checks for signed bitvector arithmetics
    /// Inserts bitvector sigend add overflow check
    virtual BoolExp *bvsaddo(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed sub overflow check
    virtual BoolExp *bvssubo(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed mul overflow check
    virtual BoolExp *bvsmulo(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed div overflow check
    virtual BoolExp *bvsdivo(BVExp*, BVExp*) = 0;

    // unsigned comparisons
    /// Inserts bitvector unsigned less or equal
    virtual BoolExp *bvule(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned greater than
    virtual BoolExp *bvugt(BVExp*, BVExp*) = 0;
    /// Inserts bitvector unsigned greater or equal
    virtual BoolExp *bvuge(BVExp*, BVExp*) = 0;

    // signed comparisons
    /// Inserts bitvector signed less than
    virtual BoolExp *bvslt(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed less or equal
    virtual BoolExp *bvsle(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed greater than
    virtual BoolExp *bvsgt(BVExp*, BVExp*) = 0;
    /// Inserts bitvector signed greater or equal
    virtual BoolExp *bvsge(BVExp*, BVExp*) = 0;

    // special case
    /// Inserts bitvector multiplicaton
    virtual BVExp *bvmul(const Bitvector *bv, BVExp *exp)
    {
        BVExp *bvexp = bv2bv(bv);
        BVExp *res = bvmul(bvexp, exp);
        release(bvexp);
        return res;
    }

    /// release the memory of BVExp
    virtual void release(BVExp*) = 0;

    /// Return the width of the bitvector \a exp.
    virtual unsigned int width(BVExp *exp) = 0;

protected:
    /// Default constructor for the theory of bitvectors
    TheoryOfBitvectors()
    {}
};

}

#endif

