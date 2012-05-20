#ifndef _FUNCS_INCLUDED
#define _FUNCS_INCLUDED

#include "..\..\..\MTParserLib\MTParserPrivate.h"
#include "..\..\..\MTParserLib\MTParser.h"

// Numerical Approximation: Derivative
class DerivativeFct : public MTFctParamTokenizer::ClientFctI
{
public:

	DerivativeFct();
	

	virtual void init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException);

	virtual const MTCHAR* getSymbol(){return _T("derivate"); }

	virtual const MTCHAR* getHelpString(){ return _T("derivate(expression, variable, point)"); }
	virtual const MTCHAR* getDescription(){ return _T("Differentiate the expression with respect to one variable at the specified point"); }	
	virtual bool isConstant();
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);		
	virtual MTFunctionI* spawn();


	~DerivativeFct();
	
private:

	void clean();

private:

	MTParser *m_pExpr;				// make sure to define pointers otherwise this will
									// lead to an infinite creation loop: a function create a
									// parser, a parser create a function...!	
	
	MTDOUBLE m_ptVal;				// shared variable value 	
};

// Numerical Approximation: Integral
class TrapezoidFct : public MTFctParamTokenizer::ClientFctI
{
public:

	TrapezoidFct();
	
	virtual void init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException);

	virtual const MTCHAR* getSymbol(){return _T("trapezoid"); }
	virtual const MTCHAR* getHelpString(){ return _T("trapezoid(expression, variable, a, b, [step=0.1])"); }
	virtual const MTCHAR* getDescription(){ return _T("Compute a numerical approximation to the integral between a and b"); }	
	virtual bool isConstant();
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);	
	virtual MTFunctionI* spawn();
	
	~TrapezoidFct();
	
private:

	void clean();

private:

	// make sure to define pointers otherwise this will
	// lead to an infinite creation loop: a function create a
	// parser, a parser create a function...!	
	MTParser *m_pExpr;									
	
	MTDOUBLE m_ptVal;
};

// Numerical Approximation: Newton-Raphson's Quadratic Solve
class SolveFct : public MTFctParamTokenizer::ClientFctI
{
public:

	SolveFct();

	virtual void init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException);	

	virtual const MTCHAR* getSymbol(){return _T("solve"); }
	virtual const MTCHAR* getHelpString(){ return _T("solve(expression, variable, result, [v0=0], [tol=0.01],[maxIter=100])"); }
	virtual const MTCHAR* getDescription(){ return _T("Solve the expression for x yielding the specified result."); }	
	virtual bool isConstant();
	virtual int getNbArgs(){ return 4; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);		
	virtual MTFunctionI* spawn();

	~SolveFct();
	
private:

	void clean();
	double d1(double pt);
	double d2(double pt);

private:

	// make sure to define pointers otherwise this will
	// lead to an infinite creation loop: a function create a
	// parser, a parser create a function...!	
	MTParser *m_pExpr;									
	
	MTDOUBLE m_ptVal;
};



#endif