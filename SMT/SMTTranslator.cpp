#include <llbmc/Solver/NondefSMTTranslator.h>
#include <llbmc/Solver/SMTTranslator.h>
#include <llbmc/Solver/SMTContext.h>
#include <llbmc/ILR/Formula.h>
#include <llbmc/ILR/Ops/ConstantIntegerOp.h>
#include <llbmc/ILR/Ops/ConstantPointerOp.h>
#include <llbmc/ILR/Ops/NondefOp.h>

#include <llbmc/Util/LLBMCException.h>
#include <llbmc/Util/Logger.h>

namespace llbmc
{

BMCSMTTranslator::BMCSMTTranslator(SMTContext &context)
  : SMTTranslatorBase(context),
    m_visitor(context),
    m_freeVars(context),
    m_asserts(NULL)
{}

BMCSMTTranslator::~BMCSMTTranslator()
{}

void BMCSMTTranslator::preFormulaVisit(Formula &formula)
{
    setFormula(formula);
    m_visitor.setFormula(formula);
    m_freeVars.setFormula(formula);
}

void BMCSMTTranslator::postFormulaVisit(Formula&)
{
    if (m_asserts != NULL) {
        solver().assertConstraint(m_asserts);
        sat().release(m_asserts);
    } else {
        SMT::BoolExp *tmp = sat().mk_false();
        solver().assertConstraint(tmp);
        sat().release(tmp);
    }
}

void BMCSMTTranslator::doOp(Op *op)
{
    if (AssertOp *assertOp = dyn_cast<AssertOp>(op)) {
        translateAssertOp(assertOp);
    } else if (AssumeOp *assumeOp = dyn_cast<AssumeOp>(op)) {
        translateAssumeOp(assumeOp);
    } else if (NondefOp *nondefOp = dyn_cast<NondefOp>(op)) {
        m_freeVars.translateNondefOp(nondefOp);
    } else {
        op->accept(&m_visitor);
    }
}

void BMCSMTTranslator::translateAssertOp(AssertOp *op)
{
    SMT::BoolExp *condition = sat().copy(mapToBoolExp(op->getConditionOperand()));
    addToBoolMap(op, condition);
    SMT::BoolExp *failure = sat().mk_not(mapToBoolExp(op->getConditionOperand()));

    if (m_asserts == NULL) {
        m_asserts = failure;
    } else {
        SMT::BoolExp *oldAsserts = m_asserts;
        m_asserts = sat().mk_or(m_asserts, failure);
        sat().release(oldAsserts);
        sat().release(failure);
    }
}

void BMCSMTTranslator::translateAssumeOp(AssumeOp *op)
{
    solver().assertConstraint(mapToBoolExp(op->getAssumptionOperand()));
}

IncrementalSMTTranslator::IncrementalSMTTranslator(SMTContext &context)
  : SMTTranslatorBase(context),
    m_visitor(context),
    m_freeVars(context),
    m_abort(false),
    m_haveCheckedIncremental(false)
{}

IncrementalSMTTranslator::~IncrementalSMTTranslator()
{}

void IncrementalSMTTranslator::preFormulaVisit(Formula &formula)
{
    setFormula(formula);
    m_visitor.setFormula(formula);
    m_freeVars.setFormula(formula);
}

void IncrementalSMTTranslator::postFormulaVisit(Formula&)
{}

void IncrementalSMTTranslator::doOp(Op *op)
{
    if (AssertOp *assertOp = dyn_cast<AssertOp>(op)) {
        solveAssertOp(assertOp);
    } else if (AssumeOp *assumeOp = dyn_cast<AssumeOp>(op)) {
        translateAssumeOp(assumeOp);
    } else if (NondefOp *nondefOp = dyn_cast<NondefOp>(op)) {
        m_freeVars.translateNondefOp(nondefOp);
    } else {
        op->accept(&m_visitor);
    }
}

void IncrementalSMTTranslator::solveAssertOp(AssertOp *op)
{
    SMT::BoolExp *condition = sat().copy(mapToBoolExp(op->getConditionOperand()));
    addToBoolMap(op, condition);
    SMT::BoolExp *failure = sat().mk_not(mapToBoolExp(op->getConditionOperand()));

    m_haveCheckedIncremental = true;
    Logger& logger = Logger::getInstance();
    logger.log(LogLevel::InfoVerbose, op->getAssertTypeString());
    logger.flush();

    solver().push();
    solver().assertConstraint(failure);
    solver().solve();
    if (solver().getResult() == SMT::Solver::Satisfiable) {
        m_abort = true;
    }
    solver().pop();
}

void IncrementalSMTTranslator::translateAssumeOp(AssumeOp *op)
{
    solver().assertConstraint(mapToBoolExp(op->getAssumptionOperand()));
}

}

