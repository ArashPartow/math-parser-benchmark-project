/** @file MTParserCompiler.h
  @brief Built-in functions
  @author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERDEFFUNCS_INCLUDED
#define _MTPARSERDEFFUNCS_INCLUDED

#include "MTParserPrivate.h"
#include <float.h>		// for _isnan and _isfinite
#include <math.h>
#include <windows.h>
#include <stdlib.h>		// for __min and __max



class SinFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("sin"); }

	virtual const MTCHAR* getHelpString(){ return _T("sin(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Sine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return sin(pArg[0]); }	

	virtual MTFunctionI* spawn() { return new SinFct(); }

};

class ArcSinFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("asin"); }

	virtual const MTCHAR* getHelpString(){ return _T("asin(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Arcsine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return asin(pArg[0]); }

	virtual MTFunctionI* spawn() { return new ArcSinFct(); }

};

class SinhFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("sinh"); }

	virtual const MTCHAR* getHelpString(){ return _T("sinh(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Hyperbolic sine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return sinh(pArg[0]); }

	virtual MTFunctionI* spawn() { return new SinhFct(); }

};

class CosFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("cos"); }

	virtual const MTCHAR* getHelpString(){ return _T("cos(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Cosine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return cos(pArg[0]); }

	virtual MTFunctionI* spawn() { return new CosFct(); }

};

class ArcCosFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("acos"); }

	virtual const MTCHAR* getHelpString(){ return _T("acos(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Arccosine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return acos(pArg[0]); }

	virtual MTFunctionI* spawn() { return new ArcCosFct(); }

};

class CoshFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("cosh"); }

	virtual const MTCHAR* getHelpString(){ return _T("cosh(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Hyperbolic cosine"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return cosh(pArg[0]); }

	virtual MTFunctionI* spawn() { return new CoshFct(); }

};

class TanFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("tan"); }

	virtual const MTCHAR* getHelpString(){ return _T("tan(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Tangent"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return tan(pArg[0]); }

	virtual MTFunctionI* spawn() { return new TanFct(); }

};

class TanhFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("tanh"); }

	virtual const MTCHAR* getHelpString(){ return _T("tanh(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Hyperbolic tangent"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return tanh(pArg[0]); }

	virtual MTFunctionI* spawn() { return new TanhFct(); }

};

class ArcTanFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("atan"); }

	virtual const MTCHAR* getHelpString(){ return _T("atan(rad)"); }
	virtual const MTCHAR* getDescription(){ return _T("Arctangent"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return atan(pArg[0]); }

	virtual MTFunctionI* spawn() { return new ArcTanFct(); }

};

class SqrtFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("sqrt"); }

	virtual const MTCHAR* getHelpString(){ return _T("sqrt(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Square root"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		
		return sqrt(pArg[0]); 		
	}

	virtual MTFunctionI* spawn() { return new SqrtFct(); }
};

class MinFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getID(){return _T("min2"); }
	virtual const MTCHAR* getSymbol(){return _T("min"); }

	virtual const MTCHAR* getHelpString(){ return _T("min(x,y)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns smaller of two values"); }	
	virtual int getNbArgs(){ return 2; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		return __min(pArg[0],pArg[1]); 
	}

	virtual MTFunctionI* spawn() { return new MinFct(); }

};

class Min3Fct : public MTFunctionI
{		
	virtual const MTCHAR* getID(){return _T("min3"); }
	virtual const MTCHAR* getSymbol(){return _T("min"); }

	virtual const MTCHAR* getHelpString(){ return _T("min(x,y,z)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns smaller of three values"); }	
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		return __min(__min(pArg[0],pArg[1]), pArg[2]); 
	}

	virtual MTFunctionI* spawn() { return new Min3Fct(); }

};

class MinUndefFct : public MTFunctionI
{		

	virtual const MTCHAR* getID(){return _T("minUndef"); }
	virtual const MTCHAR* getSymbol(){return _T("min"); }

	virtual const MTCHAR* getHelpString(){ return _T("min(v1,v2,v3,...)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns smaller of a set of values"); }	
	virtual int getNbArgs(){ return c_MTNbArgUndefined; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		MTDOUBLE min = pArg[0];
		
		for( unsigned int t=1; t<nbArgs; t++ )
		{
			if( pArg[t] < min )
			{
				min = pArg[t];
			}
		}

		return min;
	}

	virtual MTFunctionI* spawn() { return new MinUndefFct(); }
};

class MaxFct : public MTFunctionI
{		

	virtual const MTCHAR* getID(){return _T("max2"); }
	virtual const MTCHAR* getSymbol(){return _T("max"); }

	virtual const MTCHAR* getHelpString(){ return _T("max(x,y)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns larger of two values"); }	
	virtual int getNbArgs(){ return 2; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 		
		return __max(pArg[0],pArg[1]); 
	}

	virtual MTFunctionI* spawn() { return new MaxFct(); }
};

class Max3Fct : public MTFunctionI
{		
	virtual const MTCHAR* getID(){return _T("max3"); }
	virtual const MTCHAR* getSymbol(){return _T("max"); }

	virtual const MTCHAR* getHelpString(){ return _T("max(x,y,z)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns larger of three values"); }	
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 		
		return __max(__max(pArg[0],pArg[1]), pArg[2]); 
	}

	virtual MTFunctionI* spawn() { return new Max3Fct(); }
};

class MaxUndefFct : public MTFunctionI
{		

	virtual const MTCHAR* getID(){return _T("maxUndef"); }
	virtual const MTCHAR* getSymbol(){return _T("max"); }

	virtual const MTCHAR* getHelpString(){ return _T("max(v1,v2,v3,...)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns larger of a set of values"); }	
	virtual int getNbArgs(){ return c_MTNbArgUndefined; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		MTDOUBLE max = pArg[0];
		
		for( unsigned int t=1; t<nbArgs; t++ )
		{
			if( pArg[t] > max )
			{
				max = pArg[t];
			}
		}

		return max;
	}

	virtual MTFunctionI* spawn() { return new MaxUndefFct(); }
};

class AbsFct : public MTFunctionI
{		

	virtual const MTCHAR* getSymbol(){return _T("abs"); }

	virtual const MTCHAR* getHelpString(){ return _T("abs(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Absolute value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		
		return fabs(pArg[0]); 
	}

	virtual MTFunctionI* spawn() { return new AbsFct(); }
};

class RandFct : public MTFunctionI
{		

	virtual const MTCHAR* getID(){return _T("rand0"); }
	virtual const MTCHAR* getSymbol(){return _T("rand"); }

	virtual const MTCHAR* getHelpString(){ return _T("rand()"); }
	virtual const MTCHAR* getDescription(){ return _T("Random value between 0 and 1"); }	
	virtual int getNbArgs(){ return 0; }

	virtual bool isConstant(){ return false; }

	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 			
		return rand()/(double)RAND_MAX; 
	}

	virtual MTFunctionI* spawn() { return new RandFct(); }
};

class RandMinMaxFct : public MTFunctionI
{		

	virtual const MTCHAR* getID(){return _T("rand2"); }
	virtual const MTCHAR* getSymbol(){return _T("rand"); }

	virtual const MTCHAR* getHelpString(){ return _T("rand(min, max)"); }
	virtual const MTCHAR* getDescription(){ return _T("Random value between min and max"); }	
	virtual int getNbArgs(){ return 2; }

	virtual bool isConstant(){ return false; }

	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 				
		return pArg[0]+(rand()/(double)RAND_MAX)*(pArg[1]-pArg[0]); 
	}

	virtual MTFunctionI* spawn() { return new RandMinMaxFct(); }
};

class LogFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("log"); }

	virtual const MTCHAR* getHelpString(){ return _T("log(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Natural logarithm"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return log(pArg[0]); }

	virtual MTFunctionI* spawn() { return new LogFct(); }

};

class Log10Fct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("log10"); }

	virtual const MTCHAR* getHelpString(){ return _T("log10(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Base-10 logarithm"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return log10(pArg[0]); }

	virtual MTFunctionI* spawn() { return new Log10Fct(); }

};

class CeilFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("ceil"); }

	virtual const MTCHAR* getHelpString(){ return _T("ceil(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Ceiling"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return ceil(pArg[0]); }

	virtual MTFunctionI* spawn() { return new CeilFct(); }

};

class FloorFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("floor"); }

	virtual const MTCHAR* getHelpString(){ return _T("floor(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Floor"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return floor(pArg[0]); }

	virtual MTFunctionI* spawn() { return new FloorFct(); }

};

class AvgFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("avg"); }

	virtual const MTCHAR* getHelpString(){ return _T("avg(v1,v2,v3,...)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the average of a set of values"); }	
	virtual int getNbArgs(){ return c_MTNbArgUndefined; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		MTDOUBLE val = 0;

		for( unsigned int t=0; t<nbArgs; t++ )
		{
			val += pArg[t];

		}
		return val / nbArgs; 
	}

	virtual MTFunctionI* spawn() { return new AvgFct(); }

};


class SumFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("sum"); }

	virtual const MTCHAR* getHelpString(){ return _T("sum(v1,v2,v3,...)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the sum of a set of values"); }	
	virtual int getNbArgs(){ return c_MTNbArgUndefined; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		MTDOUBLE val = 0;

		for( unsigned int t=0; t<nbArgs; t++ )
		{
			val += pArg[t];

		}
		return val; 
	}

	virtual MTFunctionI* spawn() { return new SumFct(); }

};

class FactorialFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("fact"); }

	virtual const MTCHAR* getHelpString(){ return _T("fact(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the factorial of x: x*(x-1)*(x-2)*...(x-x+1)"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		int val = (int)pArg[0];
		int res = val;

		if( val <= 0 )
		{
			return 1;
		}	

		val--;
		for( ; val>1; val-- )
		{
			res *= val;
		}
		
		return res; 
	}

	virtual MTFunctionI* spawn() { return new FactorialFct(); }

};

class IfFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("if"); }

	virtual const MTCHAR* getHelpString(){ return _T("if(condition, val1, val2)"); }
	virtual const MTCHAR* getDescription(){ return _T("If the condition is true, returns val1 else returns val2."); }	
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		if(pArg[0])
		{
			return pArg[1];
		}
		else
		{
			return pArg[2];
		}
	}

	virtual MTFunctionI* spawn() { return new IfFct(); }

};

class RoundFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("round"); }

	virtual const MTCHAR* getHelpString(){ return _T("round(x)"); }
	virtual const MTCHAR* getDescription(){ return _T("Round the fractional part of a number"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 
		if( pArg[0] > 0 )
		{
			return (int)(pArg[0]+0.5);
		}
		else
		{
			return (int)(pArg[0]-0.5);
		}
	}

	virtual MTFunctionI* spawn() { return new RoundFct(); }

};

class IsNaNFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("isNaN"); }

	virtual const MTCHAR* getHelpString(){ return _T("isNan(value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns 1 if the number is a NaN value."); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 		
		return _isnan(pArg[0]);		
	}

	virtual MTFunctionI* spawn() { return new IsNaNFct(); }

};

class IsFiniteFct : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("isFinite"); }

	virtual const MTCHAR* getHelpString(){ return _T("isFinite(value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns 1 if the number is finite."); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{ 		
		return _finite(pArg[0]) != 0;		
	}

	virtual MTFunctionI* spawn() { return new IsFiniteFct(); }

};

// Hexadecimal to decimal conversion
class HexConvFunc : public MTConvFunctionI
{
public:

	
	virtual const MTCHAR* getSymbol(){return _T("hex"); }
	virtual const MTCHAR* getHelpString(){ return _T("hex(hexNumber)");}
	virtual const MTCHAR* getDescription(){ return _T("Converts an hexadecimal number to a decimal number");}	
	virtual MTDOUBLE convert(const MTSTRING &val) 
	{
		double dval = 0;
		MTCHAR *upStrTmp = new MTCHAR[val.size()+1];		
		lstrcpy(upStrTmp, val.c_str());

		CharUpper(upStrTmp);
		MTSTRING upStr = upStrTmp;
		delete []upStrTmp;
		
		for( unsigned int t=0; t<val.size(); t++ )
		{
			dval += getVal(upStr[t]) * pow(16.0, (int)(val.size() - t-1));
		}		

		return dval;
	}

	int getVal(const MTCHAR &c)
	{		
		if( c < 'A' && c >= '0')
		{
			return c - '0';
		}
		else if( c >= 'A' && c <= 'F' )
		{
			return c - 'A'+10;
		}
		else
		{
			throwConversionExcep();
		}

		return 0;	// should never get here... it's only to shutup the compiler warning
	}

	virtual MTFunctionI* spawn() { return new HexConvFunc(); }
};

// Binary to decimal conversion
class BinConvFunc : public MTConvFunctionI
{
public:

	
	virtual const MTCHAR* getSymbol(){return _T("bin"); }
	virtual const MTCHAR* getHelpString(){ return _T("bin(binNumber)");}
	virtual const MTCHAR* getDescription(){ return _T("Converts a binary number to a decimal number");}	
	virtual MTDOUBLE convert(const MTSTRING &val) 
	{
		double dval = 0;			
		
		for( unsigned int t=0; t<val.size(); t++ )
		{
			if( val[t] != '0' && val[t] != '1' )
			{
				throwConversionExcep();
			}
			
			dval += (val[t]-'0') * pow(2.0, (int)(val.size() - t-1));
		}		

		return dval;
	}

	virtual MTFunctionI* spawn() { return new BinConvFunc(); }
};



#endif