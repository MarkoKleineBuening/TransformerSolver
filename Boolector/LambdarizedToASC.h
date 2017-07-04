#ifndef SMT_BOOLECTOR_LAMBDARIZED_TOASC_H
#define SMT_BOOLECTOR_LAMBDARIZED_TOASC_H

#include "Boolector.h"

namespace SMT
{

/// \brief Boolector SMT implementation.
/// \ingroup SMT
class BoolectorLambdarizedToASC : public Boolector
{
public:
    BoolectorLambdarizedToASC(SATSolver solver);
    ~BoolectorLambdarizedToASC();

    bool hasCapability(Capability cap) const;

    BitvectorTheoryOfArrays *getBitvectorTheoryOfArrays();

private:
    BoolectorLambdarizedToASC(const BoolectorLambdarizedToASC&);
    BoolectorLambdarizedToASC &operator=(const BoolectorLambdarizedToASC&);

    class BitvectorArraysWithLambdarizedToASC;
};

}

#endif

