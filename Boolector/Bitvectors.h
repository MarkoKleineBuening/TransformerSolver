#ifndef SMT_BOOLECTOR_BITVECTORS_H
#define SMT_BOOLECTOR_BITVECTORS_H

#include <llbmc/Util/LLBMCException.h>

// round up n to the next power of two (helper for shifts)
static inline unsigned int npo2(unsigned int n)
{
    n--;
    for (unsigned int i = 1; i < sizeof(unsigned int) * 8; i *= 2) {
        n = n | (n >> i);
    }
    return n + 1;
}

// compute the binary logarithm of n (helper for shifts)
static inline unsigned int log2(unsigned int n)
{
    if (n == 1) {
        return 0;
    } else {
        return 1 + log2(n / 2);
    }
}

namespace SMT
{

class BoolectorBitvectors : public TheoryOfBitvectors
{
public:
    BoolectorBitvectors(Btor *btor)
      : m_btor(btor)
    {}

    BVExp *bitvector(unsigned int bvWidth, const std::string &name)
    {
        BoolectorSort bvSort = boolector_bitvec_sort(m_btor, static_cast<int>(bvWidth));
        return toBVExp(boolector_var(m_btor, bvSort, name.c_str()));
    }

    BVExp *copy(BVExp *exp)
    {
        return toBVExp(boolector_copy(m_btor, toBtor(exp)));
    }

    BVExp *bool2bv1(BoolExp *exp)
    {
        return toBVExp(boolector_copy(m_btor, toBtor(exp)));
    }

    BoolExp *bv12bool(BVExp *exp)
    {
        return toBoolExp(boolector_copy(m_btor, toBtor(exp)));
    }

    BoolExp *eq(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_eq(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *concat(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_concat(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *extract(unsigned int i, unsigned int j, BVExp *exp)
    {
        return toBVExp(boolector_slice(m_btor, toBtor(exp), static_cast<int>(i), static_cast<int>(j)));
    }

    BVExp *bvnot(BVExp *exp)
    {
        return toBVExp(boolector_not(m_btor, toBtor(exp)));
    }

    BVExp *bvneg(BVExp *exp)
    {
        return toBVExp(boolector_neg(m_btor, toBtor(exp)));
    }

    BVExp *bvand(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_and(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvor(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_or(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvadd(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_add(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvmul(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_mul(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvudiv(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_udiv(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvurem(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_urem(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvshl(BVExp *exp1, BVExp *exp2)
    {
        unsigned int widthVal = width(exp1);
        Bitvector widthBV(Bitvector(widthVal, widthVal));
        BVExp *widthExp = bv2bv(&widthBV);

        BoolExp *tooBig = bvuge(exp2, widthExp);

        Bitvector zeros(Bitvector(0, widthVal));
        BVExp *zerosExp = bv2bv(&zeros);

        // boolector expects exp2 to have width equal to log2 of the exp1's width
        // need to break it down because of this
        unsigned int exp1Width = width(exp1);
        unsigned int desiredExp1Width = npo2(exp1Width);
        unsigned int exp2Width = width(exp2);
        unsigned int desiredExp2Width = log2(desiredExp1Width);

        if (exp1Width != exp2Width) {
            throw LLBMCException("Shift of different bitwidths not supported!");
        }

        BVExp *realExp1 = NULL;
        // first extend exp1 to the next power of two if necessary
        if (exp1Width != desiredExp1Width) {
            realExp1 = uext(exp1, desiredExp1Width);
        } else {
            realExp1 = copy(exp1);
        }

        // now truncate ext2 as necessary (this is always necessary)
        BVExp *realExp2 = extract(desiredExp2Width - 1, 0, exp2);

        // create result and release temporaries
        BVExp *res = toBVExp(boolector_sll(m_btor, toBtor(realExp1), toBtor(realExp2)));
        release(realExp1);
        release(realExp2);

        if (exp1Width != desiredExp1Width) {
            BVExp *tmp = extract(exp1Width - 1, 0, res);
            release(res);
            res = tmp;
        }

        BVExp *finalRes = bvcond(tooBig, zerosExp, res);
        boolector_release(m_btor, toBtor(tooBig)); // need to release this the ugly way...
        release(zerosExp);
        release(res);
        return finalRes;
    }

    BVExp *bvlshr(BVExp *exp1, BVExp *exp2)
    {
        unsigned int widthVal = width(exp1);
        Bitvector widthBV(Bitvector(widthVal, widthVal));
        BVExp *widthExp = bv2bv(&widthBV);

        BoolExp *tooBig = bvuge(exp2, widthExp);

        Bitvector zeros(Bitvector(0, widthVal));
        BVExp *zerosExp = bv2bv(&zeros);

        // boolector expects exp2 to have width equal to log2 of the exp1's width
        // need to break it down because of this
        unsigned int exp1Width = width(exp1);
        unsigned int desiredExp1Width = npo2(exp1Width);
        unsigned int exp2Width = width(exp2);
        unsigned int desiredExp2Width = log2(desiredExp1Width);

        if (exp1Width != exp2Width) {
            throw LLBMCException("Shift of different bitwidths not supported!");
        }

        BVExp *realExp1 = NULL;
        // first extend exp1 to the next power of two if necessary
        if (exp1Width != desiredExp1Width) {
            realExp1 = uext(exp1, desiredExp1Width);
        } else {
            realExp1 = copy(exp1);
        }

        // now truncate ext2 as necessary (this is always necessary)
        BVExp *realExp2 = extract(desiredExp2Width - 1, 0, exp2);

        // create result and release temporaries
        BVExp *res = toBVExp(boolector_srl(m_btor, toBtor(realExp1), toBtor(realExp2)));
        release(realExp1);
        release(realExp2);

        if (exp1Width != desiredExp1Width) {
            BVExp *tmp = extract(exp1Width - 1, 0, res);
            release(res);
            res = tmp;
        }

        BVExp *finalRes = bvcond(tooBig, zerosExp, res);
        boolector_release(m_btor, toBtor(tooBig)); // need to release this the ugly way...
        release(zerosExp);
        release(res);
        return finalRes;
    }

    BoolExp *bvult(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ult(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bv2bv(const Bitvector *bv)
    {
        unsigned int bvWidth = bv->getWidth();
        if (bvWidth <= 8*sizeof(unsigned int)) {
            BoolectorSort bvSort = boolector_bitvec_sort(m_btor, static_cast<int>(bvWidth));
            return toBVExp(boolector_unsigned_int(m_btor, static_cast<unsigned int>(bv->getUnsigned()), bvSort));
        }

        // convert value into 0-1 string
        char *bits = new char[bvWidth + 1];
        bits[bvWidth] = '\0';
        for (unsigned int i = 0; i < bvWidth; ++i) {
            if (bv->getBit(i)) {
                bits[bvWidth - i - 1] = '1';
            } else {
                bits[bvWidth - i - 1] = '0';
            }
        }
        BVExp *res = toBVExp(boolector_const(m_btor, bits));
        delete[] bits;
        return res;
    }

    BVExp *bvzeros(unsigned int bvWidth)
    {
        BoolectorSort bvSort = boolector_bitvec_sort(m_btor, static_cast<int>(bvWidth));
        return toBVExp(boolector_zero(m_btor, bvSort));
    }

    BVExp *bvones(unsigned int bvWidth)
    {
        BoolectorSort bvSort = boolector_bitvec_sort(m_btor, static_cast<int>(bvWidth));
        return toBVExp(boolector_ones(m_btor, bvSort));
    }

    BVExp *uext(BVExp *exp, unsigned int newWidth)
    {
        return toBVExp(boolector_uext(m_btor, toBtor(exp), static_cast<int>(newWidth - width(exp))));
    }

    BVExp *sext(BVExp *exp, unsigned int newWidth)
    {
        return toBVExp(boolector_sext(m_btor, toBtor(exp), static_cast<int>(newWidth - width(exp))));
    }

    BoolExp *bvne(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ne(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvxor(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_xor(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvimplies(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_implies(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvcond(BoolExp *cond, BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_cond(m_btor, toBtor(cond), toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvsub(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_sub(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvsdiv(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_sdiv(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvsrem(BVExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_srem(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *bvashr(BVExp *exp1, BVExp *exp2)
    {
        unsigned int widthVal = width(exp1);
        Bitvector widthBV(Bitvector(widthVal, widthVal));
        BVExp *widthExp = bv2bv(&widthBV);

        BoolExp *tooBig = bvuge(exp2, widthExp);

        Bitvector zeros(Bitvector(0, widthVal));
        Bitvector ones(Bitvector::bvones(widthVal));
        BVExp *zerosExp = bv2bv(&zeros);
        BVExp *onesExp = bv2bv(&ones);

        BoolExp *exp1Neg = bvslt(exp1, zerosExp);
        BVExp *tooBigRes = bvcond(exp1Neg, onesExp, zerosExp);

        boolector_release(m_btor, toBtor(exp1Neg)); // need to release this the ugly way...
        release(onesExp);
        release(zerosExp);

        // boolector expects exp2 to have width equal to log2 of the exp1's width
        // need to break it down because of this
        unsigned int exp1Width = width(exp1);
        unsigned int desiredExp1Width = npo2(exp1Width);
        unsigned int exp2Width = width(exp2);
        unsigned int desiredExp2Width = log2(desiredExp1Width);

        if (exp1Width != exp2Width) {
            throw LLBMCException("Shift of different bitwidths not supported!");
        }

        BVExp *realExp1 = NULL;
        // first extend exp1 to the next power of two if necessary
        if (exp1Width != desiredExp1Width) {
            realExp1 = sext(exp1, desiredExp1Width);
        } else {
            realExp1 = copy(exp1);
        }

        // now truncate ext2 as necessary (this is always necessary)
        BVExp *realExp2 = extract(desiredExp2Width - 1, 0, exp2);

        // create result and release temporaries
        BVExp *res = toBVExp(boolector_sra(m_btor, toBtor(realExp1), toBtor(realExp2)));
        release(realExp1);
        release(realExp2);

        if (exp1Width != desiredExp1Width) {
            BVExp *tmp = extract(exp1Width - 1, 0, res);
            release(res);
            res = tmp;
        }

        BVExp *finalRes = bvcond(tooBig, tooBigRes, res);
        boolector_release(m_btor, toBtor(tooBig)); // need to release this the ugly way...
        release(tooBigRes);
        release(res);
        return finalRes;
    }

    BoolExp *bvuaddo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_uaddo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvusubo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_usubo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvumulo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_umulo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsaddo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_saddo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvssubo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ssubo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsmulo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_smulo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsdivo(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_sdivo(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvule(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ulte(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvugt(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ugt(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvuge(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_ugte(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvslt(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_slt(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsle(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_slte(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsgt(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_sgt(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *bvsge(BVExp *exp1, BVExp *exp2)
    {
        return toBoolExp(boolector_sgte(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    void release(BVExp *exp)
    {
        boolector_release(m_btor, toBtor(exp));
    }

    unsigned int width(BVExp *exp)
    {
        return static_cast<unsigned int>(boolector_get_width(m_btor, toBtor(exp)));
    }

private:
    BoolectorBitvectors(const BoolectorBitvectors&);
    BoolectorBitvectors &operator=(const BoolectorBitvectors&);

    Btor *m_btor;
};

}

#endif

