#ifndef SMT_BOOLECTOR_BITVECTOR_UFS_H
#define SMT_BOOLECTOR_BITVECTOR_UFS_H

#include "Common.h"

#include <llbmc/SMT/TheoryOfUFs.h>

namespace SMT
{

class BoolectorBVUFs : public BitvectorTheoryOfUFs
{
public:
    BoolectorBVUFs(Btor *btor)
      : m_btor(btor)
    {}

    UFExp *uf(unsigned int resSize, std::list<unsigned int> &argSizes, const std::string &name)
    {
        unsigned int num_args = argSizes.size();
        BoolectorSort *domain = new BoolectorSort[num_args];
        std::list<unsigned int>::iterator it = argSizes.begin();
        for (unsigned int i = 0; i < num_args; ++i, ++it) {
            domain[i] = boolector_bitvec_sort(m_btor, static_cast<int>(*it));
        }
        BoolectorSort codomain = boolector_bitvec_sort(m_btor, static_cast<int>(resSize));
        BoolectorSort sort = boolector_fun_sort(m_btor, domain, static_cast<int>(num_args), codomain);
        for (unsigned int i = 0; i < num_args; ++i) {
            boolector_release_sort(m_btor, domain[i]);
        }
        boolector_release_sort(m_btor, codomain);
        delete [] domain;
        UFExp *res = toUFExp(boolector_uf(m_btor, sort, name.c_str()));
        boolector_release_sort(m_btor, sort);
        return res;
    }

    UFExp *copy(UFExp *exp)
    {
        return toUFExp(boolector_copy(m_btor, toBtor(exp)));
    }

    BVExp *apply(UFExp *ufexp, std::list<BVExp*> &args)
    {
        unsigned int num_args = static_cast<unsigned int>(args.size());
        BoolectorNode **arg_array = new BoolectorNode*[num_args];
        std::list<BVExp*>::iterator it = args.begin();
        for (unsigned int i = 0; i < num_args; ++i, ++it) {
            arg_array[i] = toBtor(*it);
        }
        BVExp *res = toBVExp(boolector_apply(m_btor, arg_array, static_cast<int>(num_args), toBtor(ufexp)));
        delete [] arg_array;
        return res;
    }

    UFExp *array2ufexp(const BVArray*)
    {
        throw LLBMCException("boolector doesn't support array2ufexp");
    }

    void release(UFExp *exp)
    {
        boolector_release(m_btor, toBtor(exp));
    }

private:
    BoolectorBVUFs(const BoolectorBVUFs&);
    BoolectorBVUFs &operator=(const BoolectorBVUFs&);

    Btor *m_btor;
};

}

#endif

