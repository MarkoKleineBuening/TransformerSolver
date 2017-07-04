#include <iostream>
#include <sstream>

#include <llbmc/Util/Bitvector.h>
#include <llbmc/SMT/QF_ABV.h>
#include <llbmc/SMT/Solver.h>
#include <llbmc/SMT/STP.h>
#include <llbmc/Solver/DefaultSMTTranslator.h>
#include <llbmc/SMT/TheoryOfBitvectors.h>
#include <stp/c_interface.h>
#include "SMTTranslator.h"
#include <llbmc/SMT/SMTLIB.h>
#include <llbmc/Solver/SMTContext.h>
#include <llbmc/Output/Common.h>
#include "Solver.h"

//#include "llbmc/SMT/STP_QF_ABV.h"


class BoolExp;


llvm::raw_ostream &ostream();

/*
 * Start: F = s=3 --> s'=4
 * First Step: SMT(F) QF_ABV
 * Second Step: SAT(F) with some SMT Solver
 */
int main() {

    Solver *s = new Solver();
    s->runSMTSolver();

    return 0;
}

