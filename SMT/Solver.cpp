#include <llbmc/Solver/DetachedModel.h>
#include <llbmc/Solver/Model.h>
#include <llbmc/Solver/NondefSMTTranslator.h>
#include <llbmc/Solver/SMTTranslator.h>
#include <llbmc/Solver/Solver.h>
#include <llbmc/Solver/SolverModel.h>
#include <llbmc/Solver/SolverOptions.h>
#include <llbmc/ILR/Ops/AssertOp.h>

#include <llbmc/Util/LLBMCException.h>

#include <llbmc/SMT/Solver.h>
#include <llbmc/SMT/Solvers.h>

#include <memory>

namespace SMT
{
class Model;
}

namespace llbmc
{

typedef std::unique_ptr<BMCSMTTranslator> SmartPtrBMCSMTTranslator;
typedef std::unique_ptr<IncrementalSMTTranslator> SmartPtrIncrementalSMTTranslator;

namespace
{

Solver::Result convertResult(SMT::Solver::Result result)
{
    switch (result) {
    case SMT::Solver::Satisfiable:
        return Solver::Satisfiable;
    case SMT::Solver::Unsatisfiable:
        return Solver::Unsatisfiable;
    case SMT::Solver::Unsupported:
        return Solver::Unsupported;
    case SMT::Solver::Timeout:
        return Solver::Timeout;
    case SMT::Solver::Unknown:
    default:
        return Solver::Unknown;
    }
}


SMT::Solver *getSolver(const SolverOptions &options)
{
    SMT::Solver *solver = NULL;

    switch (options.SMTSolver) {
#ifdef WITH_BOOLECTOR
    case SolverOptions::boolector:
        solver = SMT::createBoolectorLingelingSolver();
        break;
    case SolverOptions::boolectorps:
        solver = SMT::createBoolectorPicoSATSolver();
        break;
    case SolverOptions::boolectorms:
        solver = SMT::createBoolectorMiniSatSolver();
        break;
    case SolverOptions::boolectorlambdatoasc:
        solver = SMT::createBoolectorLambdarizedToASCLingelingSolver();
        break;
    case SolverOptions::boolectorlambdatoascps:
        solver = SMT::createBoolectorLambdarizedToASCPicoSATSolver();
        break;
    case SolverOptions::boolectorlambdatoascms:
        solver = SMT::createBoolectorLambdarizedToASCMiniSatSolver();
        break;
#else
    case SolverOptions::boolector:
    case SolverOptions::boolectorps:
    case SolverOptions::boolectorms:
    case SolverOptions::boolectorlambdatoasc:
    case SolverOptions::boolectorlambdatoascps:
    case SolverOptions::boolectorlambdatoascms:
        throw LLBMCException("No Boolector support!");
#endif
#ifdef WITH_STP
    case SolverOptions::stp:
        solver = SMT::createSTPMiniSatSolver(options.STPEagerReadAxioms);
        break;
    case SolverOptions::stpmsp:
        solver = SMT::createSTPMiniSatPropagatorsSolver(options.STPEagerReadAxioms);
        break;
    case SolverOptions::stpsms:
        solver = SMT::createSTPSimplifyingMiniSatSolver(options.STPEagerReadAxioms);
        break;
    case SolverOptions::stpcms4:
# ifdef WITH_CRYPTOMINISAT4
        solver = SMT::createSTPCryptoMiniSatSolver4(options.STPEagerReadAxioms);
        break;
# else
        throw LLBMCException("No STP with CryptrMiniSat4 support!");
# endif
#else
    case SolverOptions::stp:
    case SolverOptions::stpmsp:
    case SolverOptions::stpsms:
    case SolverOptions::stpcms4:
        throw LLBMCException("No STP support!");
#endif
#ifdef WITH_Z3
    case SolverOptions::z3:
        solver = SMT::createZ3Solver();
        break;
    case SolverOptions::z3fulltoasc:
        solver = SMT::createZ3QuantifiedToASCSolver(true, true, options.LiftedToASC);
        break;
    case SolverOptions::z3arraystoasc:
        solver = SMT::createZ3QuantifiedToASCSolver(true, false, options.LiftedToASC);
        break;
    case SolverOptions::z3indicestoasc:
        solver = SMT::createZ3QuantifiedToASCSolver(false, true, options.LiftedToASC);
        break;
    case SolverOptions::z3readstoasc:
        solver = SMT::createZ3QuantifiedToASCSolver(false, false, options.LiftedToASC);
        break;
    case SolverOptions::z3lia:
        solver = SMT::createZ3BitvectorsAsIntegersSolver();
        break;
#else
    case SolverOptions::z3:
    case SolverOptions::z3fulltoasc:
    case SolverOptions::z3arraystoasc:
    case SolverOptions::z3indicestoasc:
    case SolverOptions::z3readstoasc:
    case SolverOptions::z3lia:
        throw LLBMCException("No Z3 support!");
#endif
#ifdef WITH_SONOLAR
    case SolverOptions::sonolar:
        solver = SMT::createSONOLARMiniSatSolver(options.SONOLARPreprocess);
        break;
    case SolverOptions::sonolarglucose:
        solver = SMT::createSONOLARGlucoseSolver(options.SONOLARPreprocess);
        break;
#else
    case SolverOptions::sonolar:
    case SolverOptions::sonolarglucose:
        throw LLBMCException("No SONOLAR support!");
#endif
#ifdef WITH_MATHSAT
    case SolverOptions::mathsat:
        solver = SMT::createMathSATSolver();
        break;
    case SolverOptions::mathsatlia:
        solver = SMT::createMathSATBitvectorsAsIntegersSolver();
        break;
#else
    case SolverOptions::mathsat:
    case SolverOptions::mathsatlia:
        throw LLBMCException("No MathSAT support!");
#endif
#ifdef WITH_YICES2
    case SolverOptions::yices2:
        solver = SMT::createYices2Solver();
        break;
    case SolverOptions::yices2fulltoasc:
        solver = SMT::createYices2QuantifiedToASCSolver(true, true, options.LiftedToASC);
        break;
    case SolverOptions::yices2arraystoasc:
        solver = SMT::createYices2QuantifiedToASCSolver(true, false, options.LiftedToASC);
        break;
    case SolverOptions::yices2indicestoasc:
        solver = SMT::createYices2QuantifiedToASCSolver(false, true, options.LiftedToASC);
        break;
    case SolverOptions::yices2readstoasc:
        solver = SMT::createYices2QuantifiedToASCSolver(false, false, options.LiftedToASC);
        break;
    case SolverOptions::yices2lambdatoasc:
        solver = SMT::createYices2LambdarizedToASCSolver();
        break;
    case SolverOptions::yices2lia:
        solver = SMT::createYices2BitvectorsAsIntegersSolver();
        break;
#else
    case SolverOptions::yices2:
    case SolverOptions::yices2fulltoasc:
    case SolverOptions::yices2arraystoasc:
    case SolverOptions::yices2indicestoasc:
    case SolverOptions::yices2readstoasc:
    case SolverOptions::yices2lambdatoasc:
    case SolverOptions::yices2lia:
        throw LLBMCException("No Yices2 support!");
#endif
#ifdef WITH_CVC4
    case SolverOptions::cvc4:
        solver = SMT::createCVC4Solver();
        break;
    case SolverOptions::cvc4fulltoasc:
        solver = SMT::createCVC4QuantifiedToASCSolver(true, true, options.LiftedToASC);
        break;
    case SolverOptions::cvc4arraystoasc:
        solver = SMT::createCVC4QuantifiedToASCSolver(true, false, options.LiftedToASC);
        break;
    case SolverOptions::cvc4indicestoasc:
        solver = SMT::createCVC4QuantifiedToASCSolver(false, true, options.LiftedToASC);
        break;
    case SolverOptions::cvc4readstoasc:
        solver = SMT::createCVC4QuantifiedToASCSolver(false, false, options.LiftedToASC);
        break;
    case SolverOptions::cvc4lia:
        solver = SMT::createCVC4BitvectorsAsIntegersSolver();
        break;
#else
    case SolverOptions::cvc4:
    case SolverOptions::cvc4fulltoasc:
    case SolverOptions::cvc4arraystoasc:
    case SolverOptions::cvc4indicestoasc:
    case SolverOptions::cvc4readstoasc:
    case SolverOptions::cvc4lia:
        throw LLBMCException("No CVC4 support!");
#endif
    case SolverOptions::refcountdebugger:
        solver = SMT::createRefCountDebugger();
        break;
    case SolverOptions::refcountdebuggerlia:
        solver = SMT::createBitvectorsAsIntegersSolver(SMT::createRefCountDebugger());
        break;
    default:
        throw LLBMCException("Unknown SMT solver!");
    }

    if (!solver->hasCapability(SMT::Solver::CapTheoryOfUninterpretedFunctions)) {
        solver = SMT::createUninterpretedFunctionSolver(solver);
    }

    // if the solver provides assert-assume style incremental solving use the
    // push-pop-decorator to get a solver providing push-pop style incremental
    // solving.
    if (options.Incremental) {
        if (!solver->hasCapability(SMT::Solver::CapPushPop)) {
            if (solver->hasCapability(SMT::Solver::CapAssume)) {
                solver = createPushPopDecorator(solver);
            } else {
                throw LLBMCException("Cannot use " + solver->getDescription() + " together with \"--incremental\"");
            }
        }
    }

    if (solver != NULL) {
        return solver;
    } else {
        throw LLBMCException("No proper SMT solver configured");
    }
}

}


Solver::Solver(const SolverOptions &options)
  : m_smtSolver(getSolver(options)),
    m_smtContext(NULL),
    m_result(Unknown),
    m_solverModel(NULL),
    m_detachedModel(NULL),
    m_options(options)
{
    if (options.hasTimeout()) {
        setTimeout(options.Timeout);
    }
}


Solver::~Solver()
{
    delete m_detachedModel;
    delete m_solverModel;
    delete m_smtContext;
    delete m_smtSolver;
}


void Solver::setTimeout(double seconds)
{
    if (m_smtSolver->hasCapability(SMT::Solver::CapTimeout)) {
        m_smtSolver->setTimeout(static_cast<int>(seconds+0.5));
    }
}


Solver::Result Solver::getResult() const
{
    return m_result;
}


bool Solver::hasModel() const
{
    return m_smtSolver->hasModel();
}


Model *Solver::getSolverModel()
{
    if (m_solverModel == NULL && m_smtSolver->hasModel()) {
        SMT::Model *smtModel = m_smtSolver->getModel();
        if (m_smtContext != NULL && smtModel != NULL) {
            m_solverModel = new SolverModel(m_smtContext, smtModel);
        }
    }

    return m_solverModel;
}


Model *Solver::getDetachedModel()
{
    if (m_detachedModel == NULL) {
        const Model *baseModel = getSolverModel();
        if (baseModel != NULL) {
            m_detachedModel = new DetachedModel(baseModel);
        }
    }

    return m_detachedModel;
}


Model *Solver::getPreferredModel()
{
    if (m_options.UseSMTSolverModel) {
        return getSolverModel();
    } else {
        return getDetachedModel();
    }
}


bool Solver::hasSetAndCopy() const
{
    return m_smtSolver->hasCapability(SMT::Solver::CapArraySetAndCopy);
}


bool Solver::hasFPs() const
{
    return m_smtSolver->hasCapability(SMT::Solver::CapTheoryOfFPs);
}


const std::string Solver::getDescription() const
{
    return m_smtSolver->getDescription();
}


const SolverOptions &Solver::getSolverOptions() const
{
    return m_options;
}


EagerSolver::EagerSolver(const SolverOptions &options)
  : Solver(options)
{
    // always switch on incremental solving, as this is needed for the
    // refine operation
    m_smtSolver->enableIncrementalSolving();
}


EagerSolver::~EagerSolver()
{}


void EagerSolver::solve(Formula &formula)
{
    delete m_detachedModel;
    m_detachedModel = NULL;
    delete m_solverModel;
    m_solverModel = NULL;
    delete m_smtContext;

    if (formula.isEmpty()) {
        m_result = Unsatisfiable;
        return;
    }

    m_smtContext = new SMTContext(m_smtSolver, formula.getDataLayout().getBitwidth());

    SmartPtrBMCSMTTranslator translator(!getSolverOptions().Slice ? static_cast<BMCSMTTranslator*>(new ListBasedBMCSMTTranslator(*m_smtContext)) : static_cast<BMCSMTTranslator*>(new TreeBasedBMCSMTTranslator(*m_smtContext)));

    translator->translate(formula);

    m_smtSolver->solve();
    m_result = convertResult(m_smtSolver->getResult());
}


void EagerSolver::solve(Op*)
{
    throw LLBMCException("Operation not supported");
}


void EagerSolver::excludeAssert(AssertOp *op)
{
    // Add the assertion condition as a constraint to the formula to
    // exclude this assertion from being checked
    SMT::BoolExp *condition = m_smtContext->mapToBoolExp(op->getConditionOperand());
    m_smtSolver->assertConstraint(condition);
}


void EagerSolver::refine()
{
    delete m_solverModel;
    m_solverModel = NULL;
    delete m_detachedModel;
    m_detachedModel = NULL;

    m_smtSolver->solve();
    m_result = convertResult(m_smtSolver->getResult());
}


IncrementalSolver::IncrementalSolver(const SolverOptions &options)
  : Solver(options)
{}


IncrementalSolver::~IncrementalSolver()
{}


void IncrementalSolver::solve(Formula &formula)
{
    delete m_detachedModel;
    m_detachedModel = NULL;
    delete m_solverModel;
    m_solverModel = NULL;
    delete m_smtContext;

    if (formula.isEmpty()) {
        m_result = Unsatisfiable;
        return;
    }

    m_smtContext = new SMTContext(m_smtSolver, formula.getDataLayout().getBitwidth());

    m_smtSolver->enableIncrementalSolving();

    SmartPtrIncrementalSMTTranslator translator(!getSolverOptions().Slice ? static_cast<IncrementalSMTTranslator*>(new ListBasedIncrementalSMTTranslator(*m_smtContext)) : static_cast<IncrementalSMTTranslator*>(new TreeBasedIncrementalSMTTranslator(*m_smtContext)));
    translator->translate(formula);

    if (translator->didSolve()) {
        m_result = convertResult(m_smtSolver->getResult());
    } else {
        m_result = Unsatisfiable;
    }
}

void IncrementalSolver::solve(Op *op)
{
    delete m_detachedModel;
    m_detachedModel = NULL;
    delete m_solverModel;
    m_solverModel = NULL;
    delete m_smtContext;

    m_smtContext = new SMTContext(m_smtSolver, op->getFormula()->getDataLayout().getBitwidth());

    m_smtSolver->enableIncrementalSolving();

    SmartPtrIncrementalSMTTranslator translator(!getSolverOptions().Slice ? static_cast<IncrementalSMTTranslator*>(new ListBasedIncrementalSMTTranslator(*m_smtContext)) : static_cast<IncrementalSMTTranslator*>(new TreeBasedIncrementalSMTTranslator(*m_smtContext)));
    translator->translate(op);

    if (translator->didSolve()) {
        m_result = convertResult(m_smtSolver->getResult());
    } else {
        m_result = Unsatisfiable;
    }
}


void IncrementalSolver::excludeAssert(AssertOp*)
{
    // this can e.g. be implemented by keeping a list of these assertions and
    // not even running the sat solver for these.
    throw LLBMCException("Operation currently not supported");
}


void IncrementalSolver::refine()
{
    throw LLBMCException("Operation currently not supported");
}

}
