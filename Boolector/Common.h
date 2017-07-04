#ifndef SMT_BOOLECTOR_COMMON_H
#define SMT_BOOLECTOR_COMMON_H

#include <llbmc/SMT/SatCore.h>
#include <llbmc/SMT/TheoryOfBitvectors.h>
#include <llbmc/SMT/TheoryOfArrays.h>
#include <llbmc/SMT/TheoryOfUFs.h>

extern "C" {
#include <boolector/boolector.h>
}

namespace SMT
{
static inline BoolectorNode *toBtor(BoolExp *exp)
{
    return reinterpret_cast<BoolectorNode*>(exp);
}

static inline BoolectorNode *toBtor(BVExp *exp)
{
    return reinterpret_cast<BoolectorNode*>(exp);
}

static inline BoolectorNode *toBtor(AExp *exp)
{
    return reinterpret_cast<BoolectorNode*>(exp);
}

static inline BoolectorNode *toBtor(UFExp *exp)
{
    return reinterpret_cast<BoolectorNode*>(exp);
}

static inline BoolExp *toBoolExp(BoolectorNode *exp)
{
    return reinterpret_cast<BoolExp*>(exp);
}

static inline BVExp *toBVExp(BoolectorNode *exp)
{
    return reinterpret_cast<BVExp*>(exp);
}

static inline AExp *toAExp(BoolectorNode *exp)
{
    return reinterpret_cast<AExp*>(exp);
}

static inline UFExp *toUFExp(BoolectorNode *exp)
{
    return reinterpret_cast<UFExp*>(exp);
}

}

#endif

