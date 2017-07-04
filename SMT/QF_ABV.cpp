#include <llbmc/SMT/QF_ABV.h>
#include <llbmc/Util/LLBMCException.h>

namespace SMT
{

BoolExp *QF_ABV::bvne(BVExp *exp1, BVExp *exp2)
{
    BoolExp *equal = eq(exp1, exp2);
    BoolExp *ret = mk_not(equal);
    release(equal);
    return ret;
}

BoolExp *QF_ABV::bvule(BVExp *exp1, BVExp *exp2)
{
    BoolExp *ult = bvult(exp1, exp2);
    BoolExp *equal = eq(exp1, exp2);
    BoolExp *ret = mk_or(ult, equal);
    release(ult);
    release(equal);
    return ret;
}

BoolExp *QF_ABV::bvugt(BVExp *exp1, BVExp *exp2)
{
    return bvult(exp2, exp1);
}

BoolExp *QF_ABV::bvuge(BVExp *exp1, BVExp *exp2)
{
    return bvule(exp2, exp1);
}

BoolExp *QF_ABV::bvslt(BVExp *exp1, BVExp *exp2)
{
    unsigned int w = width(exp1);

    // are exp1 and exp2 positive or negative
    BVExp *neg1 = extract(w - 1, w - 1, exp1);
    BVExp *neg2 = extract(w - 1, w - 1, exp2);
    BVExp *pos2 = bvnot(neg2);

    // values of exp1 and exp2 stripped of sign
    BVExp *val1 = extract(w - 2, 0, exp1);
    BVExp *val2 = extract(w - 2, 0, exp2);

    // exp1 is signed less than if ...
    // ... exp1 is negative and exp2 is positive
    BVExp *neg1pos2 = bvand(neg1, pos2);
    BoolExp *case1 = bv12bool(neg1pos2);

    // ... signs are equal and val1 ult val2
    BoolExp *equalSign = eq(neg1, neg2);
    BoolExp *ult = bvult(val1, val2);
    BoolExp *case2 = mk_and(equalSign, ult);

    BoolExp *ret = mk_or(case1, case2);

    // release everything except for the result
    release(neg1);
    release(neg2);
    release(pos2);

    release(val1);
    release(val2);

    release(neg1pos2);
    release(case1);

    release(equalSign);
    release(ult);
    release(case2);

    return ret;
}

BoolExp *QF_ABV::bvsle(BVExp *exp1, BVExp *exp2)
{
    BoolExp *slt = bvslt(exp1, exp2);
    BoolExp *equal = eq(exp1, exp2);
    BoolExp *ret = mk_or(slt, equal);
    release(slt);
    release(equal);
    return ret;
}

BoolExp *QF_ABV::bvsgt(BVExp *exp1, BVExp *exp2)
{
    return bvslt(exp2, exp1);
}

BoolExp *QF_ABV::bvsge(BVExp *exp1, BVExp *exp2)
{
    return bvsle(exp2, exp1);
}

BoolExp *QF_ABV::bvuaddo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *uext1 = uext(exp1, bvw + 1);
    BVExp *uext2 = uext(exp2, bvw + 1);
    BVExp *sum = bvadd(uext1, uext2);
    BVExp *tmp = extract(bvw, bvw, sum);
    BoolExp *res = bv12bool(tmp);
    release(tmp);
    release(sum);
    release(uext2);
    release(uext1);
    return res;
}

BoolExp *QF_ABV::bvusubo(BVExp *exp1, BVExp *exp2)
{
    return bvult(exp1, exp2);
}

BoolExp *QF_ABV::bvumulo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    if (bvw == 1) {
        // one bit multiplication does not overflow
        return mk_false();
    }
    BVExp **zeros2 = new BVExp*[bvw - 1];
    zeros2[0] = extract(bvw - 1, bvw - 1, exp2);
    for (unsigned int i = 1; i < bvw - 1; ++i) {
        BVExp *bit = extract(bvw - 1 - i, bvw - 1 - i, exp2);
        zeros2[i] = bvor(zeros2[i - 1], bit);
        release(bit);
    }
    BVExp *bit = extract(1, 1, exp1);
    BVExp *tmp = bvand(bit, zeros2[0]);
    release(bit);
    for (unsigned int i = 1; i < bvw - 1; ++i) {
        bit = extract(i + 1, i + 1, exp1);
        BVExp *conj = bvand(bit, zeros2[i]);
        BVExp *disj = bvor(tmp, conj);
        release(bit);
        release(conj);
        release(tmp);
        tmp = disj;
    }
    BVExp *uext1 = uext(exp1, bvw + 1);
    BVExp *uext2 = uext(exp2, bvw + 1);
    BVExp *prod = bvmul(uext1, uext2);
    bit = extract(bvw, bvw, prod);
    BVExp *disj = bvor(tmp, bit);
    release(uext1);
    release(uext2);
    release(prod);
    release(bit);
    release(tmp);
    tmp = disj;
    for (unsigned int i = 0; i < bvw - 1; ++i) {
        release(zeros2[i]);
    }
    delete [] zeros2;
    BoolExp *res = bv12bool(tmp);
    release(tmp);
    return res;
}

BoolExp *QF_ABV::bvsaddo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *neg1 = extract(bvw - 1, bvw - 1, exp1);
    BVExp *neg2 = extract(bvw - 1, bvw - 1, exp2);
    BVExp *sum = bvadd(exp1, exp2);
    BVExp *sumNeg = extract(bvw - 1, bvw - 1, sum);
    BVExp *sumPos = bvnot(sumNeg);
    BVExp *bothNeg = bvand(neg1, neg2);
    BVExp *oneNeg = bvor(neg1, neg2);
    BVExp *bothPos = bvnot(oneNeg);
    BVExp *disj1 = bvand(bothNeg, sumPos);
    BVExp *disj2 = bvand(bothPos, sumNeg);
    BVExp *tmp = bvor(disj1, disj2);
    BoolExp *res = bv12bool(tmp);
    release(tmp);
    release(disj2);
    release(disj1);
    release(bothPos);
    release(oneNeg);
    release(bothNeg);
    release(sumPos);
    release(sumNeg);
    release(sum);
    release(neg1);
    release(neg2);
    return res;
}

BoolExp *QF_ABV::bvssubo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *neg1 = extract(bvw - 1, bvw - 1, exp1);
    BVExp *neg2 = extract(bvw - 1, bvw - 1, exp2);
    BVExp *pos1 = bvnot(neg1);
    BVExp *pos2 = bvnot(neg2);
    BVExp *sub = bvsub(exp1, exp2);
    BVExp *subNeg = extract(bvw - 1, bvw - 1, sub);
    BVExp *subPos = bvnot(subNeg);
    BVExp *posneg = bvand(pos1, neg2);
    BVExp *disj1 = bvand(posneg, subNeg);
    BVExp *negpos = bvand(neg1, pos2);
    BVExp *disj2 = bvand(negpos, subPos);
    BVExp *tmp = bvor(disj1, disj2);
    BoolExp *res = bv12bool(tmp);
    release(tmp);
    release(disj2);
    release(negpos);
    release(disj1);
    release(posneg);
    release(subPos);
    release(subNeg);
    release(sub);
    release(pos2);
    release(pos1);
    release(neg2);
    release(neg1);
    return res;
}

BoolExp *QF_ABV::bvsmulo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    if (bvw == 1) {
        BVExp *tmp = bvor(exp1, exp2);
        BoolExp *res = bv12bool(tmp);
        release(tmp);
        return res;
    } else if (bvw == 2) {
        BVExp *sext1 = sext(exp1, 3);
        BVExp *sext2 = sext(exp2, 3);
        BVExp *prod = bvmul(sext1, sext2);
        BVExp *bit_2 = extract(2, 2, prod);
        BVExp *bit_1 = extract(1, 1, prod);
        BVExp *tmp = bvxor(bit_2, bit_1);
        release(sext1);
        release(sext2);
        release(prod);
        release(bit_2);
        release(bit_1);
        BoolExp *res = bv12bool(tmp);
        release(tmp);
        return res;
    } else {
        BVExp *sign1 = extract(bvw - 1, bvw - 1, exp1);
        BVExp *sign2 = extract(bvw - 1, bvw - 1, exp2);
        BVExp *sext_sign1 = sext(sign1, bvw);
        BVExp *sext_sign2 = sext(sign2, bvw);
        BVExp *xor_sign1 = bvxor(exp1, sext_sign1);
        BVExp *xor_sign2 = bvxor(exp2, sext_sign2);
        BVExp **zeros2 = new BVExp*[bvw - 2];
        zeros2[0] = extract(bvw - 2, bvw - 2, xor_sign2);
        for (unsigned int i = 1; i < bvw - 2; ++i) {
            BVExp *bit = extract(bvw - 2 - i, bvw - 2 - i, xor_sign2);
            zeros2[i] = bvor(zeros2[i - 1], bit);
            release(bit);
        }
        BVExp *bit = extract(1, 1, xor_sign1);
        BVExp *tmp = bvand(bit, zeros2[0]);
        release(bit);
        for (unsigned int i = 1; i < bvw - 2; ++i) {
            bit = extract(i + 1, i + 1, xor_sign1);
            BVExp *conj = bvand(bit, zeros2[i]);
            BVExp *disj = bvor(tmp, conj);
            release(bit);
            release(conj);
            release(tmp);
            tmp = disj;
        }
        BVExp *sext1 = sext(exp1, bvw + 1);
        BVExp *sext2 = sext(exp2, bvw + 1);
        BVExp *prod = bvmul(sext1, sext2);
        BVExp *bit_n = extract(bvw, bvw, prod);
        BVExp *bit_n_minus_1 = extract(bvw - 1, bvw - 1, prod);
        BVExp *bit_xor = bvxor(bit_n, bit_n_minus_1);
        BVExp *disj = bvor(tmp, bit_xor);
        release(sext1);
        release(sext2);
        release(sign1);
        release(sign2);
        release(sext_sign1);
        release(sext_sign2);
        release(xor_sign1);
        release(xor_sign2);
        release(prod);
        release(bit_n);
        release(bit_n_minus_1);
        release(bit_xor);
        release(tmp);
        tmp = disj;
        for (unsigned int i = 0; i < bvw - 2; ++i) {
            release(zeros2[i]);
        }
        delete [] zeros2;
        BoolExp *res = bv12bool(tmp);
        release(tmp);
        return res;
    }
}

BoolExp *QF_ABV::bvsdivo(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *tmp1 = bvones(bvw-1);
    BVExp *tmp2 = uext(tmp1, bvw);
    BVExp *tmp3 = bvones(1);
    BVExp *tmp4 = uext(tmp3, bvw);
    BVExp *min = bvadd(tmp2, tmp4);
    BVExp *ones = bvones(bvw);
    BoolExp *isMin1 = eq(exp1, min);
    BoolExp *isOnes2 = eq(exp2, ones);
    BoolExp *res = mk_and(isMin1, isOnes2);
    release(isOnes2);
    release(isMin1);
    release(ones);
    release(min);
    release(tmp3);
    release(tmp2);
    release(tmp1);
    return res;
}

BVExp *QF_ABV::uext(BVExp *exp, unsigned int newWidth)
{
    unsigned int padWidth = newWidth - width(exp);
    BVExp *pad = bvzeros(padWidth);
    BVExp *res = concat(pad, exp);
    release(pad);
    return res;
}

BVExp *QF_ABV::sext(BVExp *exp, unsigned int newWidth)
{
    unsigned int padWidth = newWidth - width(exp);
    BVExp *pad0 = bvzeros(padWidth);
    BVExp *pad1 = bvones(padWidth);
    BVExp *sign = extract(width(exp) - 1, width(exp) - 1, exp);
    BVExp *bit1 = bvones(1);
    BoolExp *neg = eq(sign, bit1);
    BVExp *concat0 = concat(pad0, exp);
    BVExp *concat1 = concat(pad1, exp);
    BVExp *res = bvcond(neg, concat1, concat0);
    release(concat1);
    release(concat0);
    release(neg);
    release(bit1);
    release(sign);
    release(pad1);
    release(pad0);
    return res;
}

BVExp *QF_ABV::bvxor(BVExp *exp1, BVExp *exp2)
{
    BVExp *notExp1 = bvnot(exp1);
    BVExp *notExp2 = bvnot(exp2);
    BVExp *tmp1 = bvand(exp1, notExp2);
    BVExp *tmp2 = bvand(notExp1, exp2);
    BVExp *res = bvor(tmp1, tmp2);
    release(tmp2);
    release(tmp1);
    release(notExp2);
    release(notExp1);
    return res;
}

BVExp *QF_ABV::bvimplies(BVExp *exp1, BVExp *exp2)
{
    BVExp *notExp1 = bvnot(exp1);
    BVExp *res = bvor(notExp1, exp2);
    release(notExp1);
    return res;
}

BVExp *QF_ABV::bvsub(BVExp *exp1, BVExp *exp2)
{
    BVExp *tmp = bvneg(exp2);
    BVExp *res = bvadd(exp1, tmp);
    release(tmp);
    return res;
}

BVExp *QF_ABV::bvsdiv(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *sign1 = extract(bvw-1, bvw-1, exp1);
    BoolExp *sign1bool = bv12bool(sign1);
    BVExp *sign2 = extract(bvw-1, bvw-1, exp2);
    BoolExp *sign2bool = bv12bool(sign2);

    // xor: must result be signed?
    BVExp *signxor = bvxor(sign1, sign2);
    BoolExp *signxorbool = bv12bool(signxor);

    // normalize exp1 and exp2
    BVExp *negexp1 = bvneg(exp1);
    BVExp *condexp1 = bvcond(sign1bool, negexp1, exp1);
    BVExp *negexp2 = bvneg(exp2);
    BVExp *condexp2 = bvcond(sign2bool, negexp2, exp2);

    // unsigned divide
    BVExp *udiv = bvudiv(condexp1, condexp2);

    // sign result if necessary
    BVExp *udivneg = bvneg(udiv);
    BVExp *res = bvcond(signxorbool, udivneg, udiv);

    // cleanup
    release(udivneg);
    release(udiv);
    release(condexp2);
    release(negexp2);
    release(condexp1);
    release(negexp1);
    release(signxorbool);
    release(signxor);
    release(sign2bool);
    release(sign2);
    release(sign1bool);
    release(sign1);

    return res;
}

BVExp *QF_ABV::bvsrem(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *sign1 = extract(bvw-1, bvw-1, exp1);
    BoolExp *sign1bool = bv12bool(sign1);
    BVExp *sign2 = extract(bvw-1, bvw-1, exp2);
    BoolExp *sign2bool = bv12bool(sign2);

    // xor: must result be signed?
    BVExp *signxor = bvxor(sign1, sign2);
    BoolExp *signxorbool = bv12bool(signxor);

    // normalize exp1 and exp2
    BVExp *negexp1 = bvneg(exp1);
    BVExp *condexp1 = bvcond(sign1bool, negexp1, exp1);
    BVExp *negexp2 = bvneg(exp2);
    BVExp *condexp2 = bvcond(sign2bool, negexp2, exp2);

    // unsigned remainder
    BVExp *urem = bvurem(condexp1, condexp2);

    // sign result if necessary
    BVExp *uremneg = bvneg(urem);
    BVExp *res = bvcond(signxorbool, uremneg, urem);

    // cleanup
    release(uremneg);
    release(urem);
    release(condexp2);
    release(negexp2);
    release(condexp1);
    release(negexp1);
    release(signxorbool);
    release(signxor);
    release(sign2bool);
    release(sign2);
    release(sign1bool);
    release(sign1);

    return res;
}

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

static inline unsigned int getShiftBits(unsigned int bvw)
{
    return log2(npo2(bvw));
}

BVExp *QF_ABV::bvArithRightShift(BVExp *exp, unsigned int amount, BoolExp *isSigned, unsigned int shiftBits)
{
    unsigned int bvw = width(exp);
    unsigned int shift = amount & ((static_cast<unsigned int>(1) << shiftBits) - 1);

    if (shift == 0) {
        return copy(exp);
    } else if (shift >= bvw) {
        BVExp *ones = bvones(bvw);
        BVExp *zeros = bvzeros(bvw);
        BVExp *res = bvcond(isSigned, ones, zeros);
        release(zeros);
        release(ones);
        return res;
    } else {
        BVExp *slice = extract(bvw - 1, shift, exp);
        BVExp *ones = bvones(shift);
        BVExp *thenbv = concat(ones, slice);
        BVExp *zeros = bvzeros(shift);
        BVExp *elsebv = concat(zeros, slice);
        BVExp *res = bvcond(isSigned, thenbv, elsebv);
        release(elsebv);
        release(thenbv);
        release(zeros);
        release(ones);
        release(slice);
        return res;
    }
}

BVExp *QF_ABV::bvashr(BVExp *exp1, BVExp *exp2)
{
    unsigned int bvw = width(exp1);
    BVExp *res = copy(exp1);

    unsigned int shiftBits = getShiftBits(bvw);

    //get the shift amount (looking only at the bits appropriate for the given width)
    BVExp *shift = extract(shiftBits - 1, 0, exp2);

    //get the sign bit to fill with
    BVExp *sign = extract(bvw-1, bvw-1, exp1);
    BoolExp *signBool = bv12bool(sign);

    //construct a big if-then-elif-elif-... with one case per possible shift amount
    for (unsigned int i = bvw-1; i != 0; --i) {
        Bitvector tmpbv(i, shiftBits);
        BoolExp *isEq = eq(shift, bv2bv(&tmpbv));
        BVExp *then = bvArithRightShift(exp1, i, signBool, shiftBits);
        BVExp *tmp = bvcond(isEq, then, res);
        release(res);
        release(then);
        release(isEq);
        res = tmp;
    }

    release(sign);
    release(signBool);
    release(shift);
    return res;
}

}

