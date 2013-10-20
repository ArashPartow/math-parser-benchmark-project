#include "MTParserTestCases.h"
#include "MTParser.h"
#include <windows.h>
#include "MTParserExcepStrEng.h"
#include "MTTools.h"

#define NUMALGOPLUGINCLSID _T("{1F6C2D74-1023-4E0F-8A6B-DBA19E6585E3}")

#define ASSERTTRUE(expr, desc) {if( !(expr) ){MTSTRING msg = _T("AssertTrue failed: "); msg  += desc; msg+= _T(". Line:");msg+=MTTools::longToS(__LINE__); reportError(msg); }}

void MTParserTestCaseI::reportError(const MTSTRING &desc)
{
	MTSTRING msg = getName();
	msg += _T("-");
	msg += _T("Test failed: ");
	msg += desc;		
	msg += _T("\n\r");
	
	OutputDebugString(msg.c_str());
	m_success = false;

}

void MTParserTestCaseI::loadNumAlgoPlugin(MTParser *pParser)
{
	try
	{
		// load the numerical algorithms plug-in
		pParser->loadPlugin(NUMALGOPLUGINCLSID);
	}
	catch( MTParserException &e )
	{
		// we don't care if the info file is missing...
		if( lstrcmp(e.getException(0)->getData().getID(), MTLOCEXCEP_InfoFileOpenFailed)!=0)
		{
			MTSTRING msg = _T("Unit test definition error: ");
			msg += e.m_description.c_str();
			reportError(msg);
		}
	}
}

//************************************************
// MTMathExprTest

MTSTRING MTParserTestMathExpr::getName()
{
	return _T("Compiler");
}

bool MTParserTestMathExpr::doTests()
{	
	addTest(_T("X"), 0, false);					// Names are case sensitive	
	addTest(_T("x"), 0, true);	
	addTest(_T("y"), 0, true);	
			
	
	addTest(_T("1"), 1, true);					// constant expression
	addTest(_T("1+2"), 3, true);
	addTest(_T("1-2"), -1, true);
	addTest(_T("1--2"), 3, true);	
	addTest(_T("2*3"), 6, true);	
	addTest(_T("4/2"), 2, true);	
	addTest(_T("2^3"), 8, true);	
	addTest(_T("10%3"), 1, true);
	addTest(_T("10.34%20"), 10.34, true);			
	addTest(_T("avg(1,1-1+2,3,(2+2))"), 2.5, true);	
	addTest(_T("sum(1,2,3,2^2)"), 10, true);	
	addTest(_T("rand()*0"), 0, true);			// function with no argument	
	addTest(_T("min(1,2,3)"), 1, true);			// overloaded function	
	addTest(_T("min(-1,2,3,4)"), -1, true);		// overloaded function	
	addTest(_T("max(1,2,3)"), 3, true);			// overloaded function	
	addTest(_T("max(1,2,3,4)"), 4, true);		// overloaded function	
	addTest(_T("ceil(0.1)"), 1, true);			
	addTest(_T("floor(2.671)"), 2, true);
	addTest(_T("1.456==1.456"), 1, true);
	addTest(_T("-1.456==-1.456"), 1, true);
	addTest(_T("-1.456==-1.4567"), 0, true);
	addTest(_T("fact(0)"), 1, true);			
	addTest(_T("fact(4)"), 24, true);	
	addTest(_T("3.45 >= 3.45"), 1, true);			
	addTest(_T("3.5 >= 3.45"), 1, true);			
	addTest(_T("3.45 > 3.45"), 0, true);			
	addTest(_T("3.45 <= 3.45"), 1, true);			
	addTest(_T("3.45 <= 3.5"), 1, true);			
	addTest(_T("3.45 < 3.5"), 1, true);			
	addTest(_T("3.5 < 3.45"), 0, true);				
	addTest(_T("3.5 > 3.45"), 1, true);		
	addTest(_T("if(!(3.45 > 3.45),1,0)"), 1, true);			
	addTest(_T("if(!(3.45 >= 3.45),1,0)"), 0, true);
	addTest(_T("12.45 != 12.451"), 1, true);			
	addTest(_T("12.45 != 12.45"), 0, true);			
	addTest(_T("0 | 0"), 0, true);			
	addTest(_T("0 | 1.34"), 1, true);	
	addTest(_T("0 & 0"), 0, true);			
	addTest(_T("0 & 1"), 0, true);			
	addTest(_T("1 & 1"), 1, true);			
	addTest(_T("10 <= rand(10,20) <= 20 "), 1, true);	
	addTest(_T("sqrt(36)"), 6, true);			
	addTest(_T("x+y+sin(0)/2^3-40.9*2"), -81.8, true);	
	addTest(_T("min(sin(x),2)"), 0, true);
	addTest(_T("max(100.98,101)"), 101, true);	
	addTest(_T("round(2.3)"), 2, true);			
	addTest(_T("round(2.5)"), 3, true);			
	addTest(_T("round(-2.3)"), -2, true);			
	addTest(_T("round(-2.5)"), -3, true);	
	addTest(_T("!0*5"), 5, true);
	
	addTest(_T("min(1,0)"), 0, true);			
	addTest(_T("min(sin(ali),2)"), 0, false);	// undefined variable "ali"
	addTest(_T("foo(sin(x),2)"), 0, false);		// undefined function "foo"	
	addTest(_T("hex(ff)"), 255, true);			// conversion function
	addTest(_T("hex(ff)+2"), 257, true);		// conversion function
	addTest(_T("min(hex(A)*2,2)"), 2, true);	// conversion function
	addTest(_T("1+(hex(ff))"), 256, true);		
	addTest(_T("bin(100)"), 4, true);		
	addTest(_T("bin(102)"), 4, false);			// 2 is an invalid boolean digit
	addTest(_T("hex(fz)"), 255, false);			// 'z': invalid string argument for the conversion function

	// unary minus/add op
	addTest(_T("-1"),-1, true);			
	addTest(_T("--1"), 1, true);			
	addTest(_T("---1"), -1, true);	
	addTest(_T("-(1)"), -1, true);	
	addTest(_T("-(1+2)"), -3, true);	
	addTest(_T("--(1)"), 1, true);	
	addTest(_T("1+-2"), -1, true);	
	addTest(_T("1+-(((1+2)))"), -2, true);		
	addTest(_T("1++2"), 3, true);	
	addTest(_T("++2"), 2, true);	
	addTest(_T("+++2"), 2, true);	
	addTest(_T("(+2)"), 2, true);	
	addTest(_T("-+2"), -2, true);	

	// brackets
	addTest(_T("-(1)+3"), 2, true);	
	addTest(_T("(2+3"), 2, false);				// missing closing bracket
	addTest(_T("(2+3-(3/2)"), 2, false);		// missing closing bracket
	addTest(_T("3/2)"), 2, false);				// missing opening bracket
	addTest(_T("(1)-2"), -1, true);	
	addTest(_T("sin(((1-1)))"), 0, true);		// tricky inside brackets
	addTest(_T("-(((-2)))+3"), 5, true);	
	addTest(_T("avg((2),4)"), 3, true);	
	addTest(_T("max(1+(2,2))"), 3, false);		// missing closing bracket before arg separator	
	addTest(_T("((((100.34))))"), 100.34, true);		// expression inside brackets
	addTest(_T("(1+((2+(1))))"), 4, true);		// expression inside brackets	
	addTest(_T("1+()"), 0, false);				// () syntax is invalid	
	addTest(_T("()"), 0, false);				// () syntax is invalid

	// argument separator
	addTest(_T("avg(2,,2)"), 0, false);			// useless ","
	addTest(_T("avg(2,2,)"), 0, false);			// useless "," at the end	
	addTest(_T("avg(,2,2)"), 0, false);			// useless "," at the beginning	
	addTest(_T("2,2"), 0, false);				// useless "," outside a function
	addTest(_T("(2*2,2)"), 0, false);			// useless "," outside a function
	
	// bad syntax	
	addTest(_T("sin(1,2)"), 0, false);			// too many arguments
	addTest(_T("sin()"), 0, false);				// not enough argument
	addTest(_T("1+2/4+"), 0, false);			// expression cannot end with an operator
	addTest(_T("sin(+))"), 0, false);			// missing + arguments
	addTest(_T("sin(-)"), 0, false);			// missing - arguments
	addTest(_T("(2+3)2"), 0, false);			// the * operator is not implicit
	addTest(_T("5.1.2+3"), 0, false);			// 5.1.2 is not a valid number

	addTest(_T("isNaN(NaN)"), 1, true);		
	addTest(_T("isNaN(0)"), 0, true);		
	addTest(_T("isNaN(1/0)"), 0, true);			// a division by zero doesn't give a NaN result

	addTest(_T("isFinite(1/0)"), 0, true);		
	addTest(_T("isFinite(sqrt(-1))"), 0, true);		
	addTest(_T("isFinite(32)"), 1, true);		


	// funtions that use custom compilers
	addTest(_T("round(abs(solve(x^2,x,36)))"), 6, true);		
	addTest(_T("round(abs(solve(x^2,x,36,0)))"), 6, true);	
	addTest(_T("round(abs(solve(x^2,x,36,0, 0.0001)))"), 6, true);		
	addTest(_T("round(abs(solve(x^2,x,36,0, 0.0001, 10)))"), 6, true);		
	addTest(_T("round(abs(solve(x^2,x,36,0, 0.0001, min(100,10))))"), 6, true);		
	addTest(_T("round(abs(solve(x^2,x,36,0, 1/1000, 10^2)))"), 6, true);			
	addTest(_T("solve(x^2+o,x,36)"), 6, false);					// undefined variable o
	addTest(_T("solve(x^2,x,g+)"), 6, false);					// bad syntax "g+"		
	addTest(_T("solve(x^2,x,36,0,sin())"), 6, false);			// bad syntax "sin()"
	addTest(_T("solve(x^2,x,36,0,0.01, min(x,)"), 6, false);	// missing closing bracket
	addTest(_T("round(derivate(x^2,x,6))"), 12, true);		
	addTest(_T("round(derivate(derivate(x^2,x,p),p,10))"), 2, true);		// second order derivative
	addTest(_T("round(derivate(x^2,x,1)"), 0, false);						// missing closing bracket
	addTest(_T("round(derivate(x^2,NaN,1))"), 0, false);						// pi is a constant!
	addTest(_T("round(derivate(x^2,x,pi+)"), 0, false);						// invalid point
	addTest(_T("round(derivate(x^2,x,)"), 0, false);						// empty argument
	addTest(_T("round(trapezoid(2*x,x,0,6))"), 36, true);		
	addTest(_T("round(trapezoid(2*x,x,6,0))"), 36, true);		
	addTest(_T("round(trapezoid(2*x,x,-3,3, 0.01))"), 0, true);		
	addTest(_T("round(trapezoid(2*x,x,-6,0))"), -36, true);		
	addTest(_T("round(trapezoid(2*x,x,0,6, 0.01))"), 36, true);		
	addTest(_T("round(trapezoid(2*x,x,0,6, 0.001))"), 36, true);		
	addTest(_T("round(trapezoid(2*x,x,0,6, ())"), 36, false);				// missing closing bracket	
	addTest(_T("round(trapezoid(2*x,x,trapezoid(2*x,x,0,5),0, 0.001))"), 625, true);		
	
	// operator precedences
	addTest(_T("-1+2*5"), 9, true);		// (-1)+2*5
	addTest(_T("1+2*5"), 11, true);		// 1+(2*5)	
	addTest(_T("2>1+2"), 0, true);		// 2>(1+2)
	addTest(_T("2<1==1"), 0, true);		// 2<(1==1)
	addTest(_T("2>4 | 4+2>3"), 1, true);		// (2>4) | ((4+2)>3)


	return runTest();
}


void MTParserTestMathExpr::addTest(MTSTRING expr, MTDOUBLE result, bool valid)
{
	TESTCASE tc;
	tc.expr = expr;
	tc.expectedResult = result;
	tc.valid = valid;

	m_testCases.push_back(tc);

}

bool MTParserTestMathExpr::runTest()
{
	MTParser parserBase;
	MTParser parser;
	parser = parserBase;	// this allows to catch error on spawn methods

	int nbTests = m_testCases.size();	
	MTDOUBLE x,y;
	x=0;
	y=0;

	loadNumAlgoPlugin(&parser);	
	
	try
	{
		

		parser.defineVar(_T("x"), &x);		
		parser.defineVar(_T("y"), &y);

		parser.evaluate();		// no expression, but this should not crash the parser
	}
	catch( MTException &e )
	{
		
		MTSTRING msg = _T("Unit test definition error: ");
		msg += e.m_description.c_str();
		reportError(msg);		
		return false;
	}


	int t;
	for( t=0; t<nbTests; t++ )
	{
		try
		{
			MTDOUBLE val = parser.evaluate(m_testCases[t].expr.c_str());

			if(!m_testCases[t].valid )
			{
				MTSTRING msg;
				msg += m_testCases[t].expr;
				msg += _T(", test no.");
				msg += MTTools::longToS(t);
				msg += _T(".  Reason->expected failed");					
				
				reportError(msg);
			}	  

			
			if( val != m_testCases[t].expectedResult )
			{
				MTSTRING msg;
				msg += m_testCases[t].expr;
				msg += _T(", test no.");
				msg += MTTools::longToS(t);				
				msg += _T(".  Reason->bad result");					
				
				reportError(msg);	
				
			}
			

		}
		catch( MTException &e)
		{
			if( m_testCases[t].valid )
			{
				MTSTRING msg;
				msg += m_testCases[t].expr;
				msg += _T(", test no.");
				msg += MTTools::longToS(t);				
				msg += _T(".  Reason->");		
				msg += e.m_description.c_str();
				
				reportError(msg);
			}

		}
	}

	return m_success;
}


//************************************************
// MTParserTestGetUsedVars

MTSTRING MTParserTestGetUsedVars::getName()
{
	return _T("GetUsedVars");
}


bool MTParserTestGetUsedVars::doTests()
{
	MTParser parser;

	MTDOUBLE x,y;	

	try
	{
		// test with explicit variable definition...
		parser.defineVar(_T("x"), &x);
		parser.defineVar(_T("y"), &y);

		parser.evaluate(_T("x+1"));
		
		ASSERTTRUE(parser.getNbUsedVars()==1, _T("only the x variable is defined"))

		if( parser.getNbUsedVars()==1 )
		{
			ASSERTTRUE(lstrcmp(parser.getUsedVar(0).c_str(), _T("x"))==0, _T("the define variable'name should be x"))
		}

		parser.evaluate(_T("x+y"));
		
		ASSERTTRUE(parser.getNbUsedVars()==2, _T("the x and the y variables are defined"))

		if( parser.getNbUsedVars()==2 )
		{
			ASSERTTRUE(lstrcmp(parser.getUsedVar(0).c_str(), _T("x"))==0, _T("the first defined variable'name should be x"))
			ASSERTTRUE(lstrcmp(parser.getUsedVar(1).c_str(), _T("y"))==0, _T("the second defined variable'name should be y"))
		}

		parser.evaluate(_T("1+2"));
		
		ASSERTTRUE(parser.getNbUsedVars()==0, _T("no defined variable"))


		parser.undefineAllVars();


		// test with the auto variable definition feature
		parser.enableAutoVarDefinition(true);	

		parser.evaluate(_T("x+1"));
		
		ASSERTTRUE(parser.getNbUsedVars()==1, _T("only the x variable is defined"))

		if( parser.getNbUsedVars()==1 )
		{
			ASSERTTRUE(lstrcmp(parser.getUsedVar(0).c_str(), _T("x"))==0, _T("the define variable'name should be x"))
		}

		parser.evaluate(_T("x+y"));
		
		ASSERTTRUE(parser.getNbUsedVars()==2, _T("the x and the y variables are defined"))

		if( parser.getNbUsedVars()==2 )
		{
			ASSERTTRUE(lstrcmp(parser.getUsedVar(0).c_str(), _T("x"))==0, _T("the first defined variable'name should be x"))
			ASSERTTRUE(lstrcmp(parser.getUsedVar(1).c_str(), _T("y"))==0, _T("the second defined variable'name should be y"))
		}

		parser.evaluate(_T("1+2"));
		
		ASSERTTRUE(parser.getNbUsedVars()==0, _T("no defined variable"))
	}
	catch(MTException &e)
	{
		MTSTRING msg = _T("Exception: ");
		msg += e.m_description.c_str();
		reportError(msg);
	}

	return m_success;

}

//************************************************
// MTParserTestParserInit

MTSTRING MTParserTestParserInit::getName()
{
	return _T("Parser initialization");
}

bool MTParserTestParserInit::doTests()
{
	MTParser parser1, parser2;

	try
	{

		MTSyntax syntax;
		syntax = parser1.getSyntax();
		syntax.argumentSeparator = ';';
		syntax.decimalPoint = ',';
		parser1.setSyntax(syntax);

		MTDOUBLE x;
		x = 1;

		parser1.defineVar(_T("x"), &x);

		MTDOUBLE c1 = 10;
		parser1.defineConst(_T("c1"), c1);

		parser1.enableAutoVarDefinition(true);

		parser1.evaluate(_T("3+2+x"));

		parser2 = parser1;		

		ASSERTTRUE(parser2.getNbUsedVars()==1, _T("one defined variable: x"))
		
		if( parser2.getNbUsedVars() == 1 )
		{
			ASSERTTRUE(lstrcmp(parser2.getUsedVar(0).c_str(), _T("x"))==0, _T("the define variable'name should be x"))
		}

		ASSERTTRUE(parser2.isAutoVarDefinitionEnabled(), _T("the auto variable definition feature is on"))

		ASSERTTRUE(parser2.getNbDefinedConsts()==2, _T("Two defined const"))
		ASSERTTRUE(parser2.evaluate() == parser1.evaluate(), _T("parser1 and parser2 should evaluate to the same value"))

		
	}
	catch( MTException &e )
	{
		MTSTRING msg = _T("Exception: ");
		msg += e.m_description.c_str();
		reportError(msg);
	}

	return m_success;
}



//************************************************
// MTParserTestVarDef

MTSTRING MTParserTestVarDef::getName()
{
	return _T("Variable definition");
}

bool MTParserTestVarDef::doTests()
{
	MTParser parser;
	MTDOUBLE x;

	// MTDEFEXCEP_VariableNotFound
	try
	{
		parser.getVarBySymbol(_T("x"));		
		ASSERTTRUE(false, _T("variable not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("variable not defined"))		
	}

	// MTDEFEXCEP_VarAlreadyDefined
	try
	{
		parser.defineVar(_T("x"), &x);
		parser.defineVar(_T("x"), &x);
		ASSERTTRUE(false, _T("variable already defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_VarAlreadyDefined)==0, _T("variable already defined"))		
	}

	// MTDEFEXCEP_VarNameNull
	try
	{
		parser.defineVar(_T(""), &x);		
		ASSERTTRUE(false, _T("null variable name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_VarNameNull)==0, _T("null variable name"))		
	}

	// MTDEFEXCEP_VarNameSpace
	try
	{
		parser.defineVar(_T("v a r"), &x);		
		ASSERTTRUE(false, _T("variable name with spaces, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_VarNameSpace)==0, _T("variable name with spaces"))		
	}

	// MTDEFEXCEP_VarNameOnlyNum
	try
	{
		parser.defineVar(_T("123"), &x);		
		ASSERTTRUE(false, _T("number only variable name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(),MTDEFEXCEP_VarNameOnlyNum)==0, _T("number only variable name"))		
	}

	// MTDEFEXCEP_VarNameConstConflict
	try
	{
		parser.defineConst(_T("c1"), 1);
		parser.defineVar(_T("c1"), &x);		
		ASSERTTRUE(false, _T("var name is the same as a defined constant, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_VarNameConstConflict)==0, _T("the variable name is the same as a defined constant"))		
	}

	// MTDEFEXCEP_VarNameSyntaxConflict
	try
	{
		parser.defineVar(_T("c,"), &x);		
		ASSERTTRUE(false, _T("variable name contains a syntax character, but no exception thrown"))	
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_VarNameSyntaxConflict)==0, _T("the variable name conatains a syntax character"))		
	}

	// may contain the decimal point character...
	try
	{
		parser.defineVar(_T("c."), &x);		
	}
	catch(MTParserException & /*e*/)
	{
		ASSERTTRUE(false, _T("variable name should be able to contain the decimal point character"))	
	}	


	return m_success;
}

//************************************************
// MTParserTestSyntaxDef

MTSTRING MTParserTestSyntaxDef::getName()
{
	return _T("Syntax definition");
}

bool MTParserTestSyntaxDef::doTests()
{	
	MTParser parser;
	MTSyntax syntax;

	
	// MTDEFEXCEP_SyntaxArgDecConflict
	try
	{
		syntax = parser.getSyntax();
		syntax.argumentSeparator = syntax.decimalPoint;
		parser.setSyntax(syntax);
		ASSERTTRUE(false, _T("decimal character=arg separator character, and no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_SyntaxArgDecConflict)==0, _T("decimal character=arg separator character"))		
	}
	
	
	
	

	

	return m_success;

}

//************************************************
// MTParserTestConstDef

MTSTRING MTParserTestConstDef::getName()
{
	return _T("Constant definition");
}

bool MTParserTestConstDef::doTests()
{
	MTParser parser;
	MTDOUBLE x;

	// MTDEFEXCEP_ConstNotFound
	try
	{		
		MTSTRING name;
		parser.getConst(-1, name, x);		
		ASSERTTRUE(false, _T("constant not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("constant not defined"))		
	}

	// MTDEFEXCEP_ConstNotFound
	try
	{		
		MTSTRING name;
		parser.getConst(parser.getNbDefinedConsts(), name, x);		
		ASSERTTRUE(false, _T("constant not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("constant not defined"))		
	}

	// MTDEFEXCEP_ConstAlreadyDefined
	try
	{
		parser.defineConst(_T("c1"), 1);
		parser.defineConst(_T("c1"), 1);
		ASSERTTRUE(false, _T("constant already defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstAlreadyDefined)==0, _T("constant already defined"))		
	}

	// MTDEFEXCEP_ConstNameNull
	try
	{
		parser.defineConst(_T(""), 1);		
		ASSERTTRUE(false, _T("null constant name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameNull)==0, _T("null constant name"))		
	}

	// MTDEFEXCEP_ConstNameSpace
	try
	{
		parser.defineConst(_T("c onst"), 1);		
		ASSERTTRUE(false, _T("constant name with spaces, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameSpace)==0, _T("constant name with spaces"))		
	}


	// MTDEFEXCEP_ConstNameOnlyNum
	try
	{
		parser.defineConst(_T("123"), 1);		
		ASSERTTRUE(false, _T("number only constant name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameOnlyNum)==0, _T("number only constant name"))		
	}

	// MTDEFEXCEP_ConstNameSyntaxConflict (decimalPoint)
	try
	{
		MTSyntax syntax = parser.getSyntax();
		MTSTRING cName;
		cName += syntax.decimalPoint;
		cName += _T("c1");

		parser.defineConst(cName.c_str(), 1);		
			
	}
	catch(MTParserException &/*e*/)
	{
		ASSERTTRUE(false, _T("const name may contain a decimal point character"))		
	}

	// MTDEFEXCEP_ConstNameSyntaxConflict (argSeparator)
	try
	{
		MTSyntax syntax = parser.getSyntax();
		MTSTRING cName;
		cName += syntax.argumentSeparator;
		cName += _T("c1");

		parser.defineConst(cName.c_str(), 1);		
		ASSERTTRUE(false, _T("const name contains a syntax element, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameSyntaxConflict)==0, _T("const name contains a syntax element"))		
	}

	

	// MTDEFEXCEP_ConstNameOpConflict
	try
	{			
		MTSTRING cName;
		cName += parser.getOp(0)->getSymbol();
		cName += _T("c1");
		parser.defineConst(cName.c_str(), 1);		
		ASSERTTRUE(false, _T("const'name contains an operator symbol, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameOpConflict)==0, _T("const'name contains an operator symbol"))		
	}

	
	// MTDEFEXCEP_ConstNameVarConflict
	try
	{
		parser.defineVar(_T("c2"), &x);		
		parser.defineConst(_T("c2"), 1);
		
		ASSERTTRUE(false, _T("var name is the same as a defined constant, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameVarConflict)==0, _T("the variable name is the same as a defined constant"))		
	}

	return m_success;
}

//************************************************
// MTParserTestMacro

MTSTRING MTParserTestMacro::getName()
{
	return _T("Macro");
}

bool MTParserTestMacro::doTests()
{
	MTParser parser;
	double y =11;

	loadNumAlgoPlugin(&parser);	

	try
	{
		parser.defineMacro(	_T("macro(x, y, z)"),
							_T("2*x+y+cos(z)"),
							_T("")	);

		double res;
		res = parser.evaluate(_T("macro(1,0,0)"));
		ASSERTTRUE(res == 3, _T("Bad result"))

		res = parser.evaluate(_T("macro(1,1,0)"));

		ASSERTTRUE(res == 4, _T("Bad result"))

		
		parser.defineVar(_T("y"), &y);
		parser.defineMacro(	_T("macro2(p)"),
							_T("derivate(x^2,x,p)"),
							_T("")	);

		ASSERTTRUE(parser.evaluate(_T("round(macro2(10))")) == 20, _T("Bad result"))
		ASSERTTRUE(parser.evaluate(_T("round(macro2(y))")) == 22, _T("Bad result"))


		
		parser.defineMacro(	_T("macro3(pt)"),
							_T("derivate(macro2(x),x,pt)+macro(1,0,0)"),
							_T("")	);	// second order derivative
							
		ASSERTTRUE(parser.evaluate(_T("round(macro3(10))")) == 5, _T("Bad result"))

		parser.defineMacro(	_T("macro4(pt,y)"),
							_T("derivate(x^2+y^2,x,pt)+y"),
							_T("")	);	// second order derivative
							
		ASSERTTRUE(parser.evaluate(_T("round(macro4(y,1))")) == 23, _T("Bad result"))
		
	}
	catch( MTException &e)
	{
		reportError(_T("Unable to define the macro: ")+MTSTRING(e.m_description.c_str()));
	}

	// Void prototype
	try
	{
		parser.defineMacro(_T(""), _T(""), _T(""));
		ASSERTTRUE(false, _T("Expected fail"))
	}
	catch( MTException )
	{
		// ok!
	}

	// Void prototype
	try
	{
		parser.defineMacro(_T("()"), _T(""), _T(""));
		ASSERTTRUE(false, _T("Expected fail"))
	}
	catch( MTException )
	{
		// ok!
	}

	// Missing closing bracket
	try
	{
		parser.defineMacro(_T("macro4("), _T(""), _T(""));
		ASSERTTRUE(false, _T("Expected fail"))
	}
	catch( MTException )
	{
		// ok!
	}

	// useless argument separator
	try
	{
		parser.defineMacro(_T("macro4(x,,y)"), _T(""), _T(""));
		ASSERTTRUE(false, _T("Expected fail"))
	}
	catch( MTException )
	{
		// ok!
	}

	// useless argument separator
	try
	{
		parser.defineMacro(_T("macro4(x,)"), _T(""), _T(""));
		ASSERTTRUE(false, _T("Expected fail"))
	}
	catch( MTException )
	{
		// ok!
	}

	// Macro without argument
	try
	{
		parser.defineMacro(_T("macro4()"), _T("1+2"), _T(""));
		
	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Unable to define a macro without argument!"))
	}

	// Undefined argument
	try
	{
		parser.defineMacro(_T("macro5(x)"), _T("x+y"), _T(""));	
		ASSERTTRUE(false, _T("Expected fail: undefined argument"))
	}
	catch( MTException )
	{
		// ok!
	}

	// Undefined argument with auto var on... should change nothing
	try
	{
		parser.enableAutoVarDefinition(true);
		parser.defineMacro(_T("macro5(x)"), _T("x+y"), _T(""));	
		ASSERTTRUE(false, _T("Expected fail: undefined argument"))
	}
	catch( MTException )
	{
		// ok!
	}

	return m_success;

}

//************************************************
// MTParserTestInternational

MTSTRING MTParserTestInternational::getName()
{
	return _T("International");
}

bool MTParserTestInternational::doTests()
{
	MTParser parser;

	loadNumAlgoPlugin(&parser);	

	try
	{
		// totally weird syntax...to avoid conflict with defined items
		MTSyntax syntax;
		syntax.argumentSeparator = '@';		
		syntax.decimalPoint = '?';

		parser.setSyntax(syntax);
		double x;
		parser.defineVar(_T("x"), &x);
		x = 1000;

		ASSERTTRUE(parser.evaluate(_T("round(1?2+2?4)"))==4, _T("Bad result"))
		ASSERTTRUE(parser.evaluate(_T("min(1?2+2?4 @ 100?9882 @ 3)"))==3, _T("Bad result"))		
		ASSERTTRUE(parser.evaluate(_T("round(abs(solve(x^2@x@36?2)))"))==6, _T("Bad result"))
		ASSERTTRUE(parser.evaluate(_T("(round(x+3?6))"))==1004, _T("Bad result"))
		
		try
		{
			parser.evaluate(_T("(3.23)"));	
			ASSERTTRUE(false, _T("the '.' character is not valid"))
		}
		catch( MTException ){};

		try
		{
			parser.evaluate(_T("(3 @ 23)"));	
			ASSERTTRUE(false, _T("Invalid use of an argument separator outside a function"))
		}
		catch( MTException ){};
	}
	catch( MTException &e)
	{		
		reportError(e.m_description.c_str());		
	}

	return m_success;

}

//************************************************
// MTParserTestConstExpr

MTSTRING MTParserTestConstExpr::getName()
{
	return _T("Constant Expressions");
}

bool MTParserTestConstExpr::doTests()
{
	MTParser parser;

	loadNumAlgoPlugin(&parser);	

	try
	{
		double x = 10;
		parser.defineVar(_T("x"), &x);

		parser.compile(_T("1+2+sin(10)"));
		ASSERTTRUE(parser.isConstant(), _T("Should be constant"))

		parser.compile(_T("x"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

		parser.compile(_T("1+x"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

		parser.compile(_T("solve(x^2,x,36)"));
		ASSERTTRUE(parser.isConstant(), _T("Should be constant"))

		parser.compile(_T("solve(x^2,x,x)"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

		parser.compile(_T("derivate(x^2,x,36)"));
		ASSERTTRUE(parser.isConstant(), _T("Should be constant"))

		parser.compile(_T("derivate(x^2,x,x)"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

		parser.compile(_T("trapezoid(x^2,x,36,0)"));
		ASSERTTRUE(parser.isConstant(), _T("Should be constant"))

		parser.compile(_T("trapezoid(x^2,x,x,0)"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

		parser.compile(_T("rand()"));
		ASSERTTRUE(!parser.isConstant(), _T("Should not be constant"))

	}
	catch( MTException &e)
	{		
		reportError(e.m_description.c_str());		
	}

	return m_success;

}

//************************************************
// MTParserTestFunctionDef

MTSTRING MTParserTestFunctionDef::getName()
{
	return _T("Function definitions");
}

bool MTParserTestFunctionDef::doTests()
{
	MTParser parser;

	// MTDEFEXCEP_FuncNotFound
	try
	{			
		parser.getFunc(-1);		
		ASSERTTRUE(false, _T("function not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("function not defined"))		
	}

	// MTDEFEXCEP_FuncNotFound
	try
	{		
		MTSTRING name;
		parser.getFunc(parser.getNbDefinedFuncs());		
		ASSERTTRUE(false, _T("function not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("function not defined"))		
	}

	// MTDEFEXCEP_FuncAlreadyDefined
	try
	{
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("sin");
		pFct->m_nbArgs = 1;
		parser.defineFunc(pFct);
		ASSERTTRUE(false, _T("function already defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncAlreadyDefined)==0, _T("function already defined"))		
	}

	// MTDEFEXCEP_FuncNameNull
	try
	{
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("");
		parser.defineFunc(pFct);		
		ASSERTTRUE(false, _T("null function name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncNameNull)==0, _T("null function name"))		
	}

	// MTDEFEXCEP_FuncNameSpace
	try
	{
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("my fct");
		parser.defineFunc(pFct);		
		ASSERTTRUE(false, _T("function name with spaces, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncNameSpace)==0, _T("function name with spaces"))		
	}

	// MTDEFEXCEP_FuncNameSyntaxConflict 
	try
	{		
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("sin(");
		parser.defineFunc(pFct);	
		ASSERTTRUE(false, _T("function name with syntax element, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncNameSyntaxConflict)==0, _T("function name contains a syntax element"))		
	}
	
	try
	{		
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("sin.");
		parser.defineFunc(pFct);					
	}
	catch(MTParserException &)
	{
		ASSERTTRUE(false, _T("function name may contain decimal point character"))		
	}	

	// MTDEFEXCEP_FuncNameOpConflict 
	try
	{		
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("sin+");
		parser.defineFunc(pFct);	
		ASSERTTRUE(false, _T("function name with operator, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncNameOpConflict)==0, _T("function name contains an operator name"))		
	}	

	// Function overloading
	try
	{		
		MyFct *pFct = new MyFct();
		pFct->m_symbol = _T("myFct1");
		pFct->m_nbArgs = 1;
		
		MyFct *pFct2 = new MyFct();
		pFct2->m_symbol = _T("myFct2");
		pFct2->m_nbArgs = 2;

		parser.defineFunc(pFct);	
		parser.defineFunc(pFct2);	

		ASSERTTRUE(parser.evaluate(_T("myFct1(1)+myFct2(1,1)")) == 2, _T("function overloading doesn't work"))		

	}
	catch(MTException &e)
	{
		ASSERTTRUE(false, _T("function overloading doesn't work: "+MTSTRING(e.m_description.c_str())))		
	}	


	return m_success;
}

//************************************************
// MTParserTestOperatorDef

MTSTRING MTParserTestOperatorDef::getName()
{
	return _T("Operator definitions");
}

bool MTParserTestOperatorDef::doTests()
{
	MTParser parser;

	// MTDEFEXCEP_OpNotFound
	try
	{			
		parser.getOp(-1);		
		ASSERTTRUE(false, _T("op not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("op not defined"))		
	}

	// MTDEFEXCEP_FuncNotFound
	try
	{		
		MTSTRING name;
		parser.getOp(parser.getNbDefinedOps());		
		ASSERTTRUE(false, _T("op not defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ItemNotFound)==0, _T("op not defined"))		
	}

	// MTDEFEXCEP_OpAlreadyDefined
	try
	{
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("+");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);
		ASSERTTRUE(false, _T("operator already defined, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{		
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpAlreadyDefined)==0, _T("operator already defined"))		
	}

	// MTDEFEXCEP_OpNameNull
	try
	{
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("null op name, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpNameNull)==0, _T("null op name"))		
	}

	// MTDEFEXCEP_OpNameSpace
	try
	{
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op 1");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("op name with spaces, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpNameSpace)==0, _T("op name with spaces"))		
	}

	// operator name may contain decimal point character...
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op.");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);				
	}
	catch(MTParserException &)
	{
		ASSERTTRUE(false, _T("op name may contain decimal point character"))			
	}	

	// MTDEFEXCEP_OpNameSyntaxConflict 
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op,");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("op name with syntax element, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpNameSyntaxConflict)==0, _T("op name contains a syntax element"))		
	}		

	// MTDEFEXCEP_OpNameSyntaxConflict 
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op(");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("op name with syntax element, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpNameSyntaxConflict)==0, _T("op name contains a syntax element"))		
	}	

	// MTDEFEXCEP_OpPrecedence (>e_MTOpPrec_FCT)
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op(");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_FCT;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("bad op precedence, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpPrecedence)==0, _T("bad op precedence"))		
	}	

	// MTDEFEXCEP_OpPrecedence < 0
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("op(");
		pOp->m_isUnary = false;
		pOp->m_prec = -1;
		parser.defineOp(pOp);		
		ASSERTTRUE(false, _T("bad op precedence, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_OpPrecedence)==0, _T("bad op precedence"))		
	}	

	// MTDEFEXCEP_FuncNameOpConflict 
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("sin");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);	
		ASSERTTRUE(false, _T("function name with operator, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_FuncNameOpConflict)==0, _T("function name contains an operator name"))		
	}		

	// MTDEFEXCEP_ConstNameOpConflict 
	try
	{		
		parser.defineConst(_T("myConst"), 10);

		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("myConst");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;
		parser.defineOp(pOp);	
		ASSERTTRUE(false, _T("constant name with operator, but no exception thrown"))		
	}
	catch(MTParserException &e)
	{
		ASSERTTRUE(lstrcmp(e.getException(0)->getData().getID(), MTDEFEXCEP_ConstNameOpConflict)==0, _T("constant name contains an operator name"))		
	}	

	// Operator overloading
	try
	{		
		MyOp *pOp = new MyOp();
		pOp->m_symbol = _T("myOp1");
		pOp->m_isUnary = false;
		pOp->m_prec = e_MTOpPrec_ADD;

		MyOp *pOp2 = new MyOp();
		pOp2->m_symbol = _T("myOp1");
		pOp2->m_isUnary = true;
		pOp2->m_prec = e_MTOpPrec_UNARY;
		
		parser.defineOp(pOp);	
		parser.defineOp(pOp2);	

		ASSERTTRUE(parser.evaluate(_T("1 myOp1 2")) == -1, _T("operator overloading doesn't work"))		
		ASSERTTRUE(parser.evaluate(_T("myOp12+3")) == 1, _T("unary op doesn't work"))		

	}
	catch(MTException &e)
	{
		ASSERTTRUE(false, _T("operator overloading doesn't work: "+MTSTRING(e.m_description.c_str())))		
	}	


	return m_success;
}

//************************************************
// MTParserTestAutoVarDef

MTSTRING MTParserTestAutoVarDef::getName()
{
	return _T("Auto Variable definition");
}

bool MTParserTestAutoVarDef::doTests()
{
	MTParser parser;

	// Validate that when the auto-var feature is off, variables are not
	// automatically defined and that an error is thrown
	try
	{		
		parser.enableAutoVarDefinition(false);
		parser.compile(_T("[myVar]"));
		ASSERTTRUE(false, _T("undefined variable, but no exception thrown"))		
	}
	catch(MTException)
	{		
	}


	// When the auto-var feature is on, undefined variables should be
	// automatically defined
	try
	{		
		parser.enableAutoVarDefinition(true);
		parser.compile(_T("myVar"));
		MTVariableI *pVar = parser.getVarBySymbol(_T("myVar"));		
	}
	catch(MTException)
	{	
		ASSERTTRUE(false, _T("the auto-var feature doesn't work!"))		
	}	

	return m_success;
}

//************************************************
// MTParserTestVoidExpr

MTSTRING MTParserTestVoidExpr::getName()
{
	return _T("Void expression");
}

bool MTParserTestVoidExpr::doTests()
{
	MTParser parser;
	
	// totally void expression should return NaN
	parser.compile(_T(""));
	ASSERTTRUE(parser.isNaN(), _T("void expression"));
	
	return m_success;
}

//************************************************
// MTParserTestUndefineVar

MTSTRING MTParserTestUndefineVar::getName()
{
	return _T("UndefineVar");
}

bool MTParserTestUndefineVar::doTests()
{
	MTParser parser;
	
	MTDOUBLE x,y,z;

	try
	{
		parser.defineVar(_T("x"), &x);
		parser.defineVar(_T("y"), &y);
		parser.defineVar(_T("z"), &z);
	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Unable to define variables"))		
	}

	// undefine an undefined variable
	try
	{
		parser.undefineVar(_T("i"));		
		ASSERTTRUE(false, _T("Undefine an undefined variable but no exception"))		
	}
	catch( MTException )
	{
		// ok
	}

	// undefine a variable
	try
	{
		parser.undefineVar(_T("y"));		
		parser.getVarBySymbol(_T("x"));
		parser.getVarBySymbol(_T("z"));
	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Error undefining y"))		
	}

	// undefine the same variable again...
	try
	{
		parser.undefineVar(_T("y"));				
		ASSERTTRUE(false, _T("Undefine an undefined variable but no exception"))		
	}
	catch( MTException )
	{
		// ok
	}

	// undefine another variable
	try
	{		
		parser.undefineVar(_T("x"));				
		parser.getVarBySymbol(_T("z"));
	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Error undefining x"))		
	}

	// undefine all variables
	try
	{
		parser.undefineAllVars();	
		parser.defineVar(_T("x"), &x);
		parser.defineVar(_T("y"), &y);
		parser.defineVar(_T("z"), &z);
	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Error undefining all variables"))		
	}	

	return m_success;
}

//************************************************
// MTParserTestUndefineConstant

MTSTRING MTParserTestUndefineConstant::getName()
{
	return _T("UndefineConstant");
}

bool MTParserTestUndefineConstant::doTests()
{
	MTParser parser;

	
	try
	{
		unsigned int initialCount = parser.getNbDefinedConsts();
		parser.defineConst(_T("myConst"), 1.0);
		parser.defineConst(_T("myConst2"), 2.0);
		parser.undefineConst(_T("myConst"));

		ASSERTTRUE(parser.getNbDefinedConsts() == initialCount+1, _T("bad constant count..."))
		ASSERTTRUE(parser.evaluate(_T("myConst2")) == 2.0, _T("bad result"))
	}
	catch( MTException e)
	{
		ASSERTTRUE(false, e.m_description.c_str())		
	}

	return m_success;

}


//************************************************
// MTParserTestUndefineFunc

MTSTRING MTParserTestUndefineFunc::getName()
{
	return _T("UndefineFunc");
}

bool MTParserTestUndefineFunc::doTests()
{
	MTParser parser;

	
	try
	{
		unsigned int initialCount = parser.getNbDefinedFuncs();	

		parser.undefineFuncsBySymbol(_T("max"));

		ASSERTTRUE(parser.getNbDefinedFuncs() == initialCount-3, _T("bad function count..."))		

		ASSERTTRUE(parser.evaluate(_T("min(3,2)")) == 2, _T("bad function result"))		

		ASSERTTRUE(parser.evaluate(_T("sqrt(9)")) == 3, _T("bad function result"))		
	}
	catch( MTException e)
	{
		ASSERTTRUE(false, e.m_description.c_str())		
	}

	return m_success;

}


//************************************************
// MTParserTestUndefineOp

MTSTRING MTParserTestUndefineOp::getName()
{
	return _T("UndefineOp");
}

bool MTParserTestUndefineOp::doTests()
{
	MTParser parser;
	
	try
	{
		unsigned int initialCount = parser.getNbDefinedOps();	

		parser.undefineOpsBySymbol(_T("-"));

		ASSERTTRUE(parser.getNbDefinedOps() == initialCount-2, _T("bad operator count..."))		

		ASSERTTRUE(parser.evaluate(_T("2+1")) == 3, _T("bad result"))		

		ASSERTTRUE(parser.evaluate(_T("2*4")) == 8, _T("bad result"))		
	}
	catch( MTException e)
	{
		ASSERTTRUE(false, e.m_description.c_str())		
	}

	return m_success;

}

//************************************************
// MTParserTestEvaluateBatch

MTSTRING MTParserTestEvaluateBatch::getName()
{
	return _T("EvaluateBatch");
}

bool MTParserTestEvaluateBatch::doTests()
{
	MTParser parser;
	
	// Create variable object
	MTDoubleVector *pX = new MTDoubleVector(_T("x"));
	MTDoubleVector *pY = new MTDoubleVector(_T("y"));

	// Now defines variables in the parser
	parser.defineVar(pX);
	parser.defineVar(pY);

	
	unsigned int nbEvals = 100;
	unsigned int t;
	
	// Allocate memory for variable values and results
	MTDOUBLE *pXVector = new MTDOUBLE[nbEvals];
	MTDOUBLE *pYVector = new MTDOUBLE[nbEvals];
	MTDOUBLE *pResults = new MTDOUBLE[nbEvals];
		
	// Generate variable values
	for(t=0; t<nbEvals; t++)
	{
		pXVector[t] = t;
		pYVector[t] = t*2;
	}	

	// Assign variable values
	pX->setValues(pXVector, nbEvals);
	pY->setValues(pYVector, nbEvals);

	try
	{		
		// Compile the expression only once
		parser.compile(_T("x"));
		
		// Evaluate the expression for all variable value in one function call
		parser.evaluateBatch(nbEvals, pResults);

		for(t=0; t<nbEvals; t++)
		{
			ASSERTTRUE(pResults[t]==pXVector[t], _T("bad result"))		
		}
		
		parser.compile(_T("x+y"));		
		parser.evaluateBatch(nbEvals, pResults);

		for(t=0; t<nbEvals; t++)
		{
			ASSERTTRUE(pResults[t]==(pXVector[t]+pYVector[t]), _T("bad result"))		
		}

		parser.compile(_T("x+y+x"));		
		parser.evaluateBatch(nbEvals, pResults);

		for(t=0; t<nbEvals; t++)
		{
			ASSERTTRUE(pResults[t]==(2*pXVector[t]+pYVector[t]), _T("bad result"))		
		}	
		

	}
	catch( MTException )
	{
		ASSERTTRUE(false, _T("Err!"))		
	}

	delete []pXVector;
	delete []pYVector;
	delete []pResults;

	return m_success;
}

//************************************************
// MTParserTestRefinedVar

MTSTRING MTParserTestRefinedVar::getName()
{
	return _T("Redefined Var");
}

bool MTParserTestRefinedVar::doTests()
{
	MTParser parser;

	loadNumAlgoPlugin(&parser);	

	try
	{
		MTDOUBLE x = 10;
		parser.defineVar(_T("x"), &x);

		ASSERTTRUE(parser.evaluate(_T("x"))==10, _T("Bad result"))		

		DummyVariable *pVar = new DummyVariable();
		pVar->m_symbol = _T("x");
		pVar->m_value = 11;

		parser.redefineVar(pVar);

		ASSERTTRUE(parser.evaluate()==11, _T("Bad result"))		

		// test the other redefineVar method		
		MTDOUBLE x2 = 12;
		parser.redefineVar(_T("x"), &x2);
		ASSERTTRUE(parser.evaluate()==12, _T("Bad result"))		

	}
	catch( MTParserException )
	{
		ASSERTTRUE(false, _T("Redefining a variable failed"))		
	}

	// Redefine an undefined variable... should fail
	try
	{
		DummyVariable *pUndefinedVar = new DummyVariable();
		pUndefinedVar->m_symbol = _T("y");

		parser.redefineVar(pUndefinedVar);		
		ASSERTTRUE(false, _T("Redefining an undefined variable should fail"))		
	}
	catch( MTParserException )
	{
		// ok!
	}

	// Redefine a variable that is not used in the current expression
	try
	{
		MTDOUBLE y = 0;
		parser.defineVar(_T("y"), &y);
		
		DummyVariable *pVar = new DummyVariable();
		pVar->m_symbol = _T("y");

		parser.redefineVar(pVar);				
	}
	catch( MTParserException )
	{
		ASSERTTRUE(false, _T("Redefining an unused variable failed"))		
	}

	try
	{
		MTDOUBLE x = 10;
		MTDOUBLE y = 1;

		parser.undefineAllVars();
		parser.defineVar(_T("x"), &x);
		parser.defineVar(_T("y"), &y);

		parser.compile(_T("x+round(derivate(x^2,x,y))"));

		DummyVariable *pVarX = new DummyVariable();
		pVarX->m_symbol = _T("x");
		pVarX->m_value = 2;

		DummyVariable *pVarY = new DummyVariable();
		pVarY->m_symbol = _T("y");
		pVarY->m_value = 20;

		parser.redefineVar(pVarX);

		ASSERTTRUE(parser.evaluate()==4, _T("Bad result"))		

		parser.redefineVar(pVarY);

		ASSERTTRUE(parser.evaluate()==42, _T("Bad result"))		
	}
	catch( MTParserException e)
	{
		ASSERTTRUE(false, _T("Complex test case failed"))		
	}
	
	return m_success;
}

//************************************************
// MTParserTestVariable

MTSTRING MTParserTestVariable::getName()
{
	return _T("Variable");
}

bool MTParserTestVariable::doTests()
{
	MTParser parser;
	MTDOUBLE value = 0;

	try
	{
		ASSERTTRUE(parser.getNbDefinedVars() == 0 , _T("no variable defined yet..."))

		parser.defineVar(_T("x"), &value);

		ASSERTTRUE(parser.getNbDefinedVars() == 1 , _T("1 var defined"))

		parser.defineVar(_T("y"), &value);

		ASSERTTRUE(parser.getNbDefinedVars() == 2 , _T("2 vars defined"))

		ASSERTTRUE(lstrcmp(parser.getVar(0)->getSymbol(), _T("x")) == 0, _T("symbol should be x"))

		parser.undefineVar(_T("x"));

		ASSERTTRUE(parser.getNbDefinedVars() == 1 , _T("1 var defined"))
		ASSERTTRUE(lstrcmp(parser.getVar(0)->getSymbol(), _T("y")) == 0, _T("symbol should be y"))

	}
	catch(MTParserException)
	{
		ASSERTTRUE(false, _T("Variable test case failed"))
	}

	return m_success;
}


//************************************************
// MTParserTestSuite


bool MTParserTestSuite::doTests()	
{	
	std::vector<MTParserTestCaseI*> tests;
	
	// *********** add test cases here ***********
	tests.push_back(new MTParserTestMathExpr());
	tests.push_back(new MTParserTestGetUsedVars());
	tests.push_back(new MTParserTestParserInit());	
	tests.push_back(new MTParserTestVarDef());
	tests.push_back(new MTParserTestSyntaxDef());
	tests.push_back(new MTParserTestConstDef());
	tests.push_back(new MTParserTestMacro());
	tests.push_back(new MTParserTestInternational());
	tests.push_back(new MTParserTestConstExpr());	
	tests.push_back(new MTParserTestFunctionDef());	
	tests.push_back(new MTParserTestOperatorDef());	
	tests.push_back(new MTParserTestAutoVarDef());
	tests.push_back(new MTParserTestVoidExpr());
	tests.push_back(new MTParserTestUndefineVar());
	tests.push_back(new MTParserTestEvaluateBatch());
	tests.push_back(new MTParserTestRefinedVar());
	tests.push_back(new MTParserTestVariable());
	tests.push_back(new MTParserTestUndefineConstant());
	tests.push_back(new MTParserTestUndefineFunc());
	tests.push_back(new MTParserTestUndefineOp());	
	
	
	// *************************************



	unsigned int t;

	bool success = true;
	for( t=0; t<tests.size(); t++ )
	{
		if(!tests[t]->doTests())
		{
			success=false;		
		}
	}

	for( t=0; t<tests.size(); t++ )
	{
		delete tests[t];
	}
	
	return success;
}

