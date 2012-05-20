#ifndef _MTPARSERTESTCASES_INCLUDED
#define _MTPARSERTESTCASES_INCLUDED

#include "MTParser.h"


// Run all test cases
class MTParserTestSuite
{
public:

	// launch the tests
	// return true if all tests passed
	bool doTests();	

};


// Abstract test case
class MTParserTestCaseI
{
public:

	
	// return the test name
	virtual MTSTRING getName() = 0;

	// launch the tests
	// return true if all tests passed
	virtual bool doTests() = 0;
	

	MTParserTestCaseI(){m_success = true;}
	virtual ~MTParserTestCaseI(){};

protected:
	
	/** @brief Log the error and set the test result to failed */
	void reportError(const MTSTRING &desc);	

	/** @brief Load the numerical algorithm plug-in */
	void loadNumAlgoPlugin(MTParser *pParser);
	
protected:

	bool m_success;

};

// Test cases for various math expressions and expected results
class MTParserTestMathExpr : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();
	

private:
	
	struct TESTCASE
	{
		MTSTRING expr;
		MTDOUBLE expectedResult;
		bool valid;
	};

	std::vector<TESTCASE> m_testCases;

	// add a test case to the test suite
	void addTest(MTSTRING expr, MTDOUBLE result, bool valid);

	// run all registered tests
	bool runTest();

};

// Test cases for the getUsedVars feature
class MTParserTestGetUsedVars : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for the parser initialization features
class MTParserTestParserInit : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for variable definition
class MTParserTestVarDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for syntax definition
class MTParserTestSyntaxDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for constant definition
class MTParserTestConstDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for macros
class MTParserTestMacro : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for international features
class MTParserTestInternational : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for constant expressions
class MTParserTestConstExpr : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for functions
class MTParserTestFunctionDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

private:

	class MyFct : public MTFunctionI
	{
	public:

		virtual const MTCHAR* getSymbol(){return m_symbol.c_str(); }

		virtual const MTCHAR* getHelpString(){ return _T("dymmy(x)"); }
		virtual const MTCHAR* getDescription(){ return _T("dummy"); }	
		virtual int getNbArgs(){ return m_nbArgs; }
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return 1; }

		virtual MTFunctionI* spawn() throw(MTParserException){ return new MyFct(); }


		unsigned int m_nbArgs;
		MTSTRING m_symbol;
	};
};

// Test cases for operators
class MTParserTestOperatorDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

private:

	class MyOp : public MTOperatorI
	{
	public:

		virtual EMTOpPrecedence getPrecedence(){return (EMTOpPrecedence)m_prec;	}	
		virtual const MTCHAR* getSymbol(){return m_symbol.c_str(); }
		virtual bool isUnaryOp(){ return m_isUnary; }	

		virtual const MTCHAR* getHelpString(){ return _T(""); }
		virtual const MTCHAR* getDescription(){ return _T(""); }	

		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){  return -pArg[0]; }

		virtual MTOperatorI* spawn(){ return new MyOp(); }

		bool m_isUnary;
		unsigned int m_prec;
		MTSTRING m_symbol;
	};
};

// Test cases for the automatic variable definition feature
class MTParserTestAutoVarDef : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for void expressions
class MTParserTestVoidExpr : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for undefineVar
class MTParserTestUndefineVar : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for undefineConstant
class MTParserTestUndefineConstant : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};


// Test cases for undefineFunc
class MTParserTestUndefineFunc : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};


// Test cases for undefineOp
class MTParserTestUndefineOp : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for evaluateBatch
class MTParserTestEvaluateBatch : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};

// Test cases for redefineVar
class MTParserTestRefinedVar : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

private:

	class DummyVariable : public MTVariableI
	{
	public:

		//*********************************
		// MTVariableI interface

		virtual const MTCHAR* getSymbol(){ return m_symbol.c_str(); }		
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return m_value; }
		
		virtual MTVariableI* spawn(){ return new DummyVariable(); }		

		MTSTRING m_symbol;
		MTDOUBLE m_value;
	};
};

// General test cases for variables
class MTParserTestVariable : public MTParserTestCaseI
{
public:

	virtual MTSTRING getName();
	virtual bool doTests();

};





#endif
