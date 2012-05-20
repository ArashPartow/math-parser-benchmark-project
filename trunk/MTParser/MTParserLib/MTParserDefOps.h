/** @file MTParserCompiler.h
  @brief Built-in operators
  @author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERDEFOPS_INCLUDED
#define _MTPARSERDEFOPS_INCLUDED

#include "MTParserPrivate.h"
#include <math.h>
#include <windows.h>

class AddOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_ADD;	}	
	virtual const MTCHAR* getSymbol(){return _T("+"); }

	virtual const MTCHAR* getHelpString(){ return _T("x + y"); }
	virtual const MTCHAR* getDescription(){ return _T("Addition operator"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return pArg[0] + pArg[1]; }

	virtual MTOperatorI* spawn() { return new AddOp(); }
};

class UnaryAddOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_UNARY;	}

	virtual const MTCHAR* getID(){return _T("unaryAdd"); }
	virtual const MTCHAR* getSymbol(){return _T("+"); }  

	virtual const MTCHAR* getHelpString(){ return _T("+x" ); }
	virtual const MTCHAR* getDescription(){ return _T("Unary addition operator"); }	
	virtual bool isUnaryOp(){ return true; }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		
		return pArg[0]; 
	}

	virtual MTOperatorI* spawn() { return new UnaryAddOp(); }
};


class MinusOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_ADD;	}

	virtual const MTCHAR* getID(){return _T("minus"); }
	virtual const MTCHAR* getSymbol(){return _T("-"); }

	virtual const MTCHAR* getHelpString(){ return _T("x - y"); }
	virtual const MTCHAR* getDescription(){ return _T("Minus operator"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		return pArg[0] - pArg[1]; 
	}

	virtual MTOperatorI* spawn() { return new MinusOp(); }


};

class UnaryMinusOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_UNARY;	}

	virtual const MTCHAR* getID(){return _T("unaryMinus"); }
	virtual const MTCHAR* getSymbol(){return _T("-"); }  

	virtual const MTCHAR* getHelpString(){ return _T("-x" ); }
	virtual const MTCHAR* getDescription(){ return _T("Unary minus operator"); }	
	virtual bool isUnaryOp(){ return true; }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		
		return -pArg[0]; 
	}

	virtual MTOperatorI* spawn() { return new UnaryMinusOp(); }
};

class MultOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_MULT;	}

	
	virtual const MTCHAR* getSymbol(){return _T("*"); }

	virtual const MTCHAR* getHelpString(){ return _T("x * y"); }
	virtual const MTCHAR* getDescription(){ return _T("Multiplication operator"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return pArg[0] * pArg[1]; }

	virtual MTOperatorI* spawn() { return new MultOp(); }

};

class DivOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_MULT;	}


	virtual const MTCHAR* getSymbol(){return _T("/"); }

	virtual const MTCHAR* getHelpString(){ return _T("x / y"); }
	virtual const MTCHAR* getDescription(){ return _T("Division operator"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return pArg[0] / pArg[1]; }

	virtual MTOperatorI* spawn() { return new DivOp(); }

};

class ExpOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_EXP;	}

	
	virtual const MTCHAR* getSymbol(){return _T("^"); }

	virtual const MTCHAR* getHelpString(){ return _T("x ^ y"); }
	virtual const MTCHAR* getDescription(){ return _T("Power operator. Calculates x raised to the power of y"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		if( (int)pArg[1] == pArg[1] )
		{
			// use the faster pow method
			return pow(pArg[0], (int)pArg[1]); 
		}
		else
		{
			return pow(pArg[0], pArg[1]); 
		}
	}

	virtual MTOperatorI* spawn() { return new ExpOp(); }
};

class ModuloOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_MULT;	}

	
	virtual const MTCHAR* getSymbol(){return _T("%"); }

	virtual const MTCHAR* getHelpString(){ return _T("x % y"); }
	virtual const MTCHAR* getDescription(){ return _T("Modulo; find remainder of the division of x by y"); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return fmod(pArg[0], pArg[1]); }

	virtual MTOperatorI* spawn() { return new ModuloOp(); }

};

class GreaterThanOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_GREATERTHAN;	}

	
	virtual const MTCHAR* getSymbol(){return _T(">"); }

	virtual const MTCHAR* getHelpString(){ return _T("x > y"); }
	virtual const MTCHAR* getDescription(){ return _T("Greater than logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return pArg[0]> pArg[1]; }

	virtual MTOperatorI* spawn() { return new GreaterThanOp(); }

};

class LesserThanOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_GREATERTHAN;	}

	
	virtual const MTCHAR* getSymbol(){return _T("<"); }

	virtual const MTCHAR* getHelpString(){ return _T("x < y"); }
	virtual const MTCHAR* getDescription(){ return _T("Lesser than logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return pArg[0]< pArg[1]; }

	virtual MTOperatorI* spawn() { return new LesserThanOp(); }

};

class GreaterEqualThanOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_GREATERTHAN;	}

	
	virtual const MTCHAR* getSymbol(){return _T(">="); }

	virtual const MTCHAR* getHelpString(){ return _T("x >= y"); }
	virtual const MTCHAR* getDescription(){ return _T("Greater than or equal logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){return pArg[0]>= pArg[1]; }

	virtual MTOperatorI* spawn() { return new GreaterEqualThanOp(); }

};

class LesserEqualThanOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_GREATERTHAN;	}

	
	virtual const MTCHAR* getSymbol(){return _T("<="); }

	virtual const MTCHAR* getHelpString(){ return _T("x <= y"); }
	virtual const MTCHAR* getDescription(){ return _T("Lesser than or equal logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return pArg[0]<= pArg[1]; }

	virtual MTOperatorI* spawn() { return new LesserEqualThanOp(); }

};

class NotEqualOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_EQUAL;	}

	
	virtual const MTCHAR* getSymbol(){return _T("!="); }

	virtual const MTCHAR* getHelpString(){ return _T("x != y"); }
	virtual const MTCHAR* getDescription(){ return _T("Not equal logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return pArg[0] != pArg[1]; }

	virtual MTOperatorI* spawn() { return new NotEqualOp(); }

};

class EqualOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_COMPARISON_EQUAL;	}

	
	virtual const MTCHAR* getSymbol(){return _T("=="); }

	virtual const MTCHAR* getHelpString(){ return _T("x == y"); }
	virtual const MTCHAR* getDescription(){ return _T("Equal logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return pArg[0] == pArg[1]; }

	virtual MTOperatorI* spawn() { return new EqualOp(); }

};

class AndOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_LOGICAL_AND;	}

	
	virtual const MTCHAR* getSymbol(){return _T("&"); }

	virtual const MTCHAR* getHelpString(){ return _T("x & y"); }
	virtual const MTCHAR* getDescription(){ return _T("And logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return pArg[0] && pArg[1]; }

	virtual MTOperatorI* spawn() { return new AndOp(); }

};

class OrOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_LOGICAL_OR;	}

	
	virtual const MTCHAR* getSymbol(){return _T("|"); }

	virtual const MTCHAR* getHelpString(){ return _T("x | y"); }
	virtual const MTCHAR* getDescription(){ return _T("Or logical operator.  Returns 1 if true, 0 if false."); }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return pArg[0] || pArg[1]; }

	virtual MTOperatorI* spawn() { return new OrOp(); }

};

class NotOp : public MTOperatorI
{
	
	virtual EMTOpPrecedence getPrecedence(){return e_MTOpPrec_UNARY;	}

	
	virtual const MTCHAR* getSymbol(){return _T("!"); }  

	virtual const MTCHAR* getHelpString(){ return _T("!x" ); }
	virtual const MTCHAR* getDescription(){ return _T("Not logical operator. Returns 1 if x is 0, else returns 1"); }	
	virtual bool isUnaryOp(){ return true; }	
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		if( pArg[0] != 0 )
		{
			return 0;
		}
		else
		{
			return 1;
		}		
	}

	virtual MTOperatorI* spawn() { return new NotOp(); }
};



#endif