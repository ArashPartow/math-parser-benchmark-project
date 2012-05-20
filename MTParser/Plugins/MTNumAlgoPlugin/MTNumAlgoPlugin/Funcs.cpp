#include "Funcs.h"
#include <float.h>
#include <math.h>

#include "..\..\..\MTParserLib\MTTools.h"

//*************************************
// DerivativeFct

#define DERIVATE_H		0.0001
#define DERIVATE_2H		0.0002
#define DERIVATE_12H	0.0012


DerivativeFct::DerivativeFct()
{
	m_pExpr = NULL;
}

DerivativeFct::~DerivativeFct()
{
	clean();	
}

void DerivativeFct::clean()
{
	if( m_pExpr != NULL )
	{
		delete m_pExpr;
		m_pExpr = NULL;
	}
}

MTDOUBLE DerivativeFct::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{ 		
	// f'(pt) = ( -f(pt+2h)+8f(pt+h)-8f(pt-h)+f(pt-2h) )/(12h)
	
	double pt = pArg[0];
	
	m_ptVal = pt+DERIVATE_2H;
	double f2h = m_pExpr->evaluate();

	m_ptVal = pt+DERIVATE_H;
	double fh = m_pExpr->evaluate();

	m_ptVal = pt-DERIVATE_H;
	double fmh = m_pExpr->evaluate();

	m_ptVal = pt-DERIVATE_2H;
	double fm2h = m_pExpr->evaluate();

	return (-f2h + 8.0*fh - 8.0*fmh + fm2h) / DERIVATE_12H;		
}

bool DerivativeFct::isConstant()
{
	// if only one var used, this is the local iterator
	return m_pExpr->getNbUsedVars() == 1;
}

void DerivativeFct::init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException)
{
	clean();

	// param 0:		expression
	// param 1:		variable's name
	// param 2:		point

	if( params.size() != 3 )
	{
		// invalid number of arguments!
		pCompiler->throwParsingExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, pos, getSymbol(), params.size());		
	}

	m_pExpr = new MTParser(pCompiler, pRegistrar);
	
	m_pExpr->getCompiler()->setParent(pCompiler);			
	// force variables to be defined by the parent...
	m_pExpr->enableAutoVarDefinition(false);
	m_pExpr->undefineAllVars();
	
	int argNumber;	
	try
	{	
		// begin by defining the variable in order to be able to compile
		argNumber = 2;
		m_pExpr->defineVar(params[1].c_str(), &m_ptVal);

		argNumber = 1;
		m_pExpr->compile(params[0].c_str());

		argNumber = 3;
		pCompiler->pushFuncArg(params[2].c_str());
	}
	catch(MTParserException &e)
	{				
		
		MTRETHROW( MTExcepData(	MTPARSINGEXCEP_InvalidFuncSyntax,
								MTEXCEPARG_ITEMNAME, getSymbol(),
								MTEXCEPARG_POS, MTTools::longToS(pos).c_str(),
								MTEXCEPARG_PARAM1, MTTools::longToS(argNumber).c_str()),
								e)
	}		
}

MTFunctionI* DerivativeFct::spawn()
{ 
	return new DerivativeFct(); 
}

//*************************************
// TrapezoidFct

TrapezoidFct::TrapezoidFct()
{
	m_pExpr = NULL;	
}

TrapezoidFct::~TrapezoidFct()
{
	clean();	
}

void TrapezoidFct::clean()
{
	if( m_pExpr != NULL )
	{
		delete m_pExpr;
		m_pExpr = NULL;
	}
}

MTDOUBLE TrapezoidFct::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{ 		

	double a = pArg[0];
	double b = pArg[1];	
	double step = fabs(pArg[2]);		// make sure to take a positive number
	double stepd2 = step / 2.0;

	if( step == 0 )
	{
		return 0;	// avoid infinite loop!
	}

	// make sure that b is greater than a
	if( a > b )
	{
		double t = a;
		a = b;
		b = t;
	}
	
	m_ptVal = a;

	double lastPt = m_pExpr->evaluate();
	double curPt;
	double curPos = a+step;
	double res = 0;	

	while( curPos <= b )
	{
		m_ptVal = curPos;
		curPt = m_pExpr->evaluate();		
		res += (lastPt+curPt)*stepd2;
		lastPt = curPt;
		curPos += step;
	}

	return res;	
}

bool TrapezoidFct::isConstant()
{
	return m_pExpr->getNbUsedVars() == 1;
}

void TrapezoidFct::init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException)
{
	clean();

	// param 0	expression
	// param 1	variable's name
	// param 2	first point
	// param 3	second point
	// param 4	step (optional)

	if( params.size() != 4 && params.size() != 5)
	{
		// invalid number of arguments!
		pCompiler->throwParsingExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, pos, getSymbol(), params.size());		
	}

	MTSTRING precision = MTTools::doubleToS(0.1, pRegistrar->getSyntax().decimalPoint,1);
	if( params.size() == 5 )
	{
		precision = params[4];
	}

	m_pExpr = new MTParser(pCompiler, pRegistrar);
	
	m_pExpr->getCompiler()->setParent(pCompiler);			
	// force variables to be defined by the parent...
	m_pExpr->enableAutoVarDefinition(false);
	m_pExpr->undefineAllVars();

	
	int argNumber;	
	try
	{	
		
		argNumber = 2;
		// begin by defining the variable in order to be able to compile
		// define the variable locally, pointing to our member variable
		m_pExpr->defineVar(params[1].c_str(), &m_ptVal);

		argNumber = 1;
		m_pExpr->compile(params[0].c_str());

		argNumber = 3;
		pCompiler->pushFuncArg(params[2].c_str());		

		argNumber = 4;
		pCompiler->pushFuncArg(params[3].c_str());		

		argNumber = 5;
		pCompiler->pushFuncArg(precision.c_str());

	}
	catch(MTParserException &e)
	{		

		MTRETHROW( MTExcepData(	MTPARSINGEXCEP_InvalidFuncSyntax,
								MTEXCEPARG_ITEMNAME, getSymbol(),
								MTEXCEPARG_POS, MTTools::longToS(pos).c_str(),
								MTEXCEPARG_PARAM1, MTTools::longToS(argNumber).c_str()),
								e)
	}			
}


MTFunctionI* TrapezoidFct::spawn()
{ 
	return new TrapezoidFct(); 
}

//*************************************
// SolveFct

SolveFct::SolveFct()
{
	m_pExpr = NULL;	
}

SolveFct::~SolveFct()
{
	clean();	
}

void SolveFct::clean()
{
	if( m_pExpr != NULL )
	{
		delete m_pExpr;
		m_pExpr = NULL;
	}
}

inline double SolveFct::d1(double pt)
{
	m_ptVal = pt+DERIVATE_2H;
	double f2h = m_pExpr->evaluate();

	m_ptVal = pt+DERIVATE_H;
	double fh = m_pExpr->evaluate();

	m_ptVal = pt-DERIVATE_H;
	double fmh = m_pExpr->evaluate();

	m_ptVal = pt-DERIVATE_2H;
	double fm2h = m_pExpr->evaluate();

	return (-f2h + 8.0*fh - 8.0*fmh + fm2h) / DERIVATE_12H;		
}

inline double SolveFct::d2(double pt)
{	
	double f2h = d1(pt+DERIVATE_2H);
	double fh = d1(pt+DERIVATE_H);
	double fmh = d1(pt-DERIVATE_H);	
	double fm2h = d1(pt-DERIVATE_2H);

	return (-f2h + 8.0*fh - 8.0*fmh + fm2h) / DERIVATE_12H;	
}

MTDOUBLE SolveFct::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{ 		

	double tol = pArg[2];
	int maxIter = (int)pArg[3];

	if( maxIter <= 0 )
	{
		return 0;
	}

	double exprVal = pArg[0];
	double xold = pArg[1];
	double xnew = 0;
	double fVal, d1fVal, d2fVal;
	double err = tol+1;		// current error
	double fValOnd1fVal;	// fVal/d1fVal
	int t = 0;				// iteration counter


	// Newton's algorithm tries to find one zero
	// The expression we solve is: expr-val=0

	while( t<maxIter && err > tol )
	{
		m_ptVal = xold;
		fVal = m_pExpr->evaluate()-exprVal;

		d1fVal = d1(xold);

		// the first derivate must not be too small, otherwise the
		// algorithm will explode
		if( fabs(d1fVal) > DERIVATE_H )
		{				
			d2fVal = d2(xold);
			fValOnd1fVal = fVal/d1fVal;

			xnew = xold - fValOnd1fVal - 0.5*d2fVal/d1fVal * pow(fValOnd1fVal,2);

			err = fabs( xnew - xold );
			xold = xnew;
		}
		else
		{
			xold += 1;		// try to move out of this hole!
		}

		t++;
	}

	return xnew;	
}

bool SolveFct::isConstant()
{
	return m_pExpr->getNbUsedVars() == 1;
}

void SolveFct::init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException)
{
	clean();	
	
	// param 0	expression
	// param 1	variable's name
	// param 2	expression's value
	// param 3	initial approximation (optional)
	// param 4	tolerance (optional)
	// param 5	maxIteration (optional)

	if( params.size() < 3 || params.size() > 6)
	{
		// invalid number of arguments!
		pCompiler->throwParsingExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, pos, getSymbol(), params.size());		
	}	

	MTSTRING v0 = _T("0");
	MTSTRING tol = MTTools::doubleToS(0.01, pRegistrar->getSyntax().decimalPoint,2);
	MTSTRING maxIter = _T("100");	

	if( params.size() >= 4 )
	{
		v0 = params[3];
		if( params.size() >= 5 )
		{
			tol = params[4];

			if( params.size() == 6 )
			{
				maxIter = params[5];
			}
		}
	}	

	m_pExpr = new MTParser(pCompiler, pRegistrar);
	
	m_pExpr->undefineAllVars();
	// force variables to be defined by the parent...
	m_pExpr->enableAutoVarDefinition(false);
	m_pExpr->getCompiler()->setParent(pCompiler);			
	
	int argNumber;	
	try
	{			
		argNumber = 2;
		// begin by defining the variable in order to be able to compile
		// define the variable locally, pointing to our member variable
		m_pExpr->defineVar(params[1].c_str(), &m_ptVal);	

		argNumber = 1;
		m_pExpr->compile(params[0].c_str());			

		argNumber = 3;
		pCompiler->pushFuncArg(params[2].c_str());			

		argNumber = 4;
		pCompiler->pushFuncArg(v0.c_str());				

		argNumber = 5;
		pCompiler->pushFuncArg(tol.c_str());			

		argNumber = 6;
		pCompiler->pushFuncArg(maxIter.c_str());		
	}
	catch(MTParserException &e)
	{				

		MTRETHROW( MTExcepData(	MTPARSINGEXCEP_InvalidFuncSyntax,
								MTEXCEPARG_ITEMNAME, getSymbol(),
								MTEXCEPARG_POS, MTTools::longToS(pos).c_str(),
								MTEXCEPARG_PARAM1, MTTools::longToS(argNumber).c_str()),
								e)
	}	
}

MTFunctionI* SolveFct::spawn()
{ 
	return new SolveFct(); 
}