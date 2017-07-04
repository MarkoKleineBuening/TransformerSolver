//
// Created by marko on 23.06.17.
//

#include <iostream>
#include "SMTTranslator.h"

SMTTranslator::SMTTranslator(llbmc::SMTContext &context) : SMTTranslatorBase(context) {

}

SMT::BVExp *SMTTranslator::createBV(std::string name, int width){
    SMT::BVExp *s = bv().bitvector(width, name);
    return s;
}

SMT::BVExp *SMTTranslator::createConst(int value, int width) {
    SMT::BVExp *constant = bv().bv2bv(new Bitvector(value, width));
    return constant;
}




SMT::BoolExp *SMTTranslator::bvAssignValue(SMT::BVExp *bitvector, int value) {
    SMT::BVExp *s = bitvector;
    SMT::BVExp *constant = bv().bv2bv(new Bitvector(value, bv().width(bitvector)));
    SMT::BoolExp *an = bv().eq(s, constant);
    return an;
}

SMT::BoolExp *SMTTranslator::bvAssignValueNeg(SMT::BVExp *bitvector, int value) {
    SMT::BVExp *s = bitvector;
    SMT::BVExp *constant = bv().bv2bv(new Bitvector(value, bv().width(bitvector)));
    SMT::BoolExp *an = bv().bvne(s, constant);
    return an;
}

SMT::BoolExp *SMTTranslator::bvAssignNegationValue(SMT::BVExp *bitvector, int value) {
    SMT::BVExp *s = bitvector;
    SMT::BVExp *constant = bv().bv2bv(new Bitvector(value, bv().width(bitvector)));
    SMT::BVExp *negation = bv().bvneg(constant);
    SMT::BoolExp *an = bv().eq(s, negation);
    return an;
}

SMT::BoolExp *SMTTranslator::compareSlt(SMT::BVExp *a, SMT::BVExp *b){
    SMT::BoolExp *ret = bv().bvslt(a,b);
    return ret;
}





//-------------------------------//

SMT::BoolExp *SMTTranslator::bvImplies(SMT::BVExp *an, SMT::BVExp *cn, SMT::SatCore *pCore) {

    SMT::BVExp * neg = bv().bvnot(an);
    SMT::BVExp *orAC = bv().bvor(neg, cn);
    SMT::BoolExp *bo = bv().bv12bool(orAC);
    return  bo;
}

SMT::BoolExp *SMTTranslator::archiv() {
    SMT::BVExp *s = bv().bitvector(4, "s");
    SMT::BVExp *sDash = bv().bitvector(4, "sDash");
    SMT::BVExp *const3 = bv().bv2bv(new Bitvector(3, 4));
    SMT::BVExp *const4 = bv().bv2bv(new Bitvector(4, 4));

    SMT::BoolExp *an = bv().eq(s, const3);
    SMT::BoolExp *cn = bv().eq(sDash, const4);

    SMT::BVExp *anBV = bv().bool2bv1(an);
    SMT::BVExp *cnBV = bv().bool2bv1(cn);
    SMT::BVExp *branch = bv().bvimplies(anBV, cnBV);

    SMT::BVExp *a = bv().bvand(cnBV, bv().bvneg(branch));
    SMT::BVExp *b = bv().bvand(branch, bv().bvneg(cnBV));
    SMT::BVExp *c = bv().bvand(a, b);
    SMT::BVExp *d = bv().bvand(c, bv().bvneg(c));
    SMT::BVExp *e = bv().bvand(d, bv().bvnot(c));
    SMT::BVExp *branchNot = bv().bvneg(branch);


    SMT::BoolExp *f = bv().bv12bool(e);

    SMT::BVExp *const5 = bv().bv2bv(new Bitvector(5, 4));
    SMT::BVExp *const6 = bv().bv2bv(new Bitvector(6, 4));
    SMT::BoolExp *eqUnsat = bv().eq(const5, const6);

    return eqUnsat;
}

/*
 * returns: s=3 --> s'= 4
 */
SMT::BoolExp *SMTTranslator::visitSimpleBranch() {
    SMT::BVExp *s = bv().bitvector(4, "s");
    SMT::BVExp *sDash = bv().bitvector(4, "sDash");
    SMT::BVExp *const3 = bv().bv2bv(new Bitvector(3, 4));
    SMT::BVExp *const4 = bv().bv2bv(new Bitvector(4, 4));

    SMT::BoolExp *an = bv().eq(s, const3);
    SMT::BoolExp *cn = bv().eq(sDash, const4);

    SMT::BVExp *anBV = bv().bool2bv1(an);
    SMT::BVExp *cnBV = bv().bool2bv1(cn);
    SMT::BVExp *anda = bv().bvmul(anBV, cnBV);
    SMT::BVExp *branch = bv().bvimplies(anBV, cnBV);

    SMT::BoolExp *outSat = bv().bv12bool(branch);
    return outSat;
}

SMT::BoolExp *SMTTranslator::visitSimpleBranchCorrect() {
    SMT::BVExp *s = bv().bitvector(4, "s");
    SMT::BVExp *sDash = bv().bitvector(4, "sDash");
    SMT::BVExp *const3 = bv().bv2bv(new Bitvector(3, 4));
    SMT::BVExp *const4 = bv().bv2bv(new Bitvector(4, 4));

    SMT::BoolExp *an = bv().eq(s, const3);
    SMT::BoolExp *cn = bv().eq(sDash, const4);

    SMT::BVExp *branch = bv().bvimplies(s, sDash);

    SMT::BoolExp *outSat = bv().bv12bool(branch);
    return outSat;
}









