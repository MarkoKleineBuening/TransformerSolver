//
// Created by marko on 23.06.17.
//

#ifndef TRANSFORMERSOLVER_SMTTRANSLATOR_H
#define TRANSFORMERSOLVER_SMTTRANSLATOR_H


#include <llbmc/Solver/DefaultSMTTranslator.h>


class SMTTranslator  : public llbmc::SMTTranslatorBase {

public:

    SMTTranslator(llbmc::SMTContext &context);

    SMT::BoolExp * visitSimpleBranch();

    SMT::BoolExp *archiv();

    SMT::BoolExp *visitSimpleBranchCorrect();

    SMT::BVExp *createBV(std::string name, int width);

    SMT::BoolExp *bvAssignValue(SMT::BVExp *bitvector, int value);

    SMT::BoolExp *compareSlt(SMT::BVExp *a, SMT::BVExp *b);

    SMT::BoolExp *bvImplies(SMT::BVExp *an, SMT::BVExp *cn, SMT::SatCore *pCore);

    SMT::BVExp *createConst();

    SMT::BVExp *createConst(int value, int width);

    SMT::BoolExp *bvAssignNegationValue(SMT::BVExp *pExp, int i);

    SMT::BoolExp *bvAssignValueNeg(SMT::BVExp *pExp, int i);
};


#endif //TRANSFORMERSOLVER_SMTTRANSLATOR_H
