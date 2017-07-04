#ifndef SMT_BOOLECTOR_SAT_H
#define SMT_BOOLECTOR_SAT_H

#include "Common.h"

namespace SMT
{

class BoolectorSatCore : public SatCore
{
public:
    BoolectorSatCore(Btor *btor)
      : m_btor(btor)
    {}

    BoolExp *mk_free(const std::string &name)
    {
        return toBoolExp(boolector_var(m_btor, boolector_bitvec_sort(m_btor, 1), name.c_str()));
    }

    BoolExp *mk_true()
    {
        return toBoolExp(boolector_ones(m_btor, boolector_bitvec_sort(m_btor, 1)));
    }

    BoolExp *mk_false()
    {
        return toBoolExp(boolector_zero(m_btor, boolector_bitvec_sort(m_btor, 1)));
    }

    BoolExp *mk_not(BoolExp *exp)
    {
        return toBoolExp(boolector_not(m_btor, toBtor(exp)));
    }

    BoolExp *mk_and(BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_and(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *mk_or(BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_or(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *mk_xor(BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_xor(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *mk_implies(BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_implies(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *mk_iff(BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_iff(m_btor, toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *mk_cond(BoolExp *cond, BoolExp *exp1, BoolExp *exp2)
    {
        return toBoolExp(boolector_cond(m_btor, toBtor(cond), toBtor(exp1), toBtor(exp2)));
    }

    BoolExp *copy(BoolExp* exp)
    {
        return toBoolExp(boolector_copy(m_btor, toBtor(exp)));
    }

    void release(BoolExp *exp)
    {
        boolector_release(m_btor, toBtor(exp));
    }

private:
    BoolectorSatCore(const BoolectorSatCore&);
    BoolectorSatCore &operator=(const BoolectorSatCore&);

    Btor *m_btor;
};

}

#endif

