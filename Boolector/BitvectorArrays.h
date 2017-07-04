#ifndef SMT_BOOLECTOR_BITVECTOR_ARRAYS_H
#define SMT_BOOLECTOR_BITVECTOR_ARRAYS_H

#include "Common.h"

#include <llbmc/Util/LLBMCException.h>

namespace SMT
{

class BoolectorBVArrays : public BitvectorTheoryOfArrays
{
public:
    BoolectorBVArrays(Btor *btor)
      : m_btor(btor)
    {}

    AExp *array(unsigned int indexWidth, unsigned int elementWidth, const std::string &name)
    {
        BoolectorSort arraySort = boolector_array_sort(m_btor,
            boolector_bitvec_sort(m_btor, static_cast<int>(indexWidth)),
            boolector_bitvec_sort(m_btor, static_cast<int>(elementWidth)));
        return toAExp(boolector_array(m_btor, arraySort, name.c_str()));
    }

    AExp *copy(AExp* exp)
    {
        return toAExp(boolector_copy(m_btor, toBtor(exp)));
    }

    BoolExp *eq(AExp *exp1, AExp *exp2)
    {
        return toBoolExp(boolector_eq(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BVExp *read(AExp *exp1, BVExp *exp2)
    {
        return toBVExp(boolector_read(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    AExp *write(AExp *exp1, BVExp *exp2, BVExp *exp3)
    {
        return toAExp(boolector_write(m_btor, toBtor(exp1), toBtor(exp2), toBtor(exp3)));
    }

    AExp *memcpy(AExp*, BVExp*, AExp*, BVExp*, BVExp*)
    {
        throw LLBMCException("boolector doesn't support memcpy of arrays");
    }

    AExp *memset(AExp*, BVExp*, BVExp*, BVExp*)
    {
        throw LLBMCException("boolector doesn't support memset of arrays");
    }

    AExp *array2exp(const BVArray*)
    {
        throw LLBMCException("boolector doesn't support array2exp");
    }

    AExp *acond(BoolExp *cond, AExp *exp1, AExp *exp2)
    {
        return toAExp(boolector_cond(m_btor, toBtor(cond), toBtor(exp1), toBtor(exp2)));
    }

    void release(AExp *exp)
    {
        boolector_release(m_btor, toBtor(exp));
    }

private:
    BoolectorBVArrays(const BoolectorBVArrays&);
    BoolectorBVArrays &operator=(const BoolectorBVArrays&);

    Btor *m_btor;
};

}

#endif

