// MTParser.cpp : Implementation of CMTParser
#include "stdafx.h"
#include "MTParserCOM.h"
#include "MTParser.h"
#include ".\mtparser.h"
#include "../MTParserLib/MTTools.h"
#include "../MTParserLib/MTParserLocalizer.h"


/////////////////////////////////////////////////////////////////////////////
// CMTParser

STDMETHODIMP CMTParser::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMTParser
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CMTParser::CMTParser()
{
	m_pUnkMarshaler = NULL;	
	m_pParser = new MTParser();	
}

CMTParser::~CMTParser()
{
	delete m_pParser;

}


STDMETHODIMP CMTParser::evaluate(BSTR expr, double *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	MTSTRING exprStr = toMTSTRING(expr);

	try
	{
		*pResult = m_pParser->evaluate(exprStr.c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}

STDMETHODIMP CMTParser::compile(BSTR expr)
{
	MTSTRING exprStr = toMTSTRING(expr);

	try
	{
		m_pParser->compile(exprStr.c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}


	return S_OK;
}

STDMETHODIMP CMTParser::evaluateCompiled(double *pResult)
{	
	
	*pResult = m_pParser->evaluate();	

	return S_OK;
}

STDMETHODIMP CMTParser::resetExpression()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	m_pParser->resetExpression();

	return S_OK;
}

STDMETHODIMP CMTParser::undefineVar(BSTR symbol)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	try
	{
		m_pParser->undefineVar(symbol);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}

STDMETHODIMP CMTParser::undefineAllVars()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	m_pParser->undefineAllVars();

	return S_OK;
}

STDMETHODIMP CMTParser::defineFunc(IMTFunction *pFunc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	CComPtr<IMTFunction> funcPtr = pFunc;	

	if( funcPtr == NULL )
	{
		return Error( _T("Invalid function object (cannot be null)."), __uuidof( IMTParser ), E_FAIL  );
	}	
	
	try
	{	

		FunctionWrapper* pFuncWrapper = new FunctionWrapper();
		pFuncWrapper->init(funcPtr);
		m_pParser->defineFunc(pFuncWrapper);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
		

	return S_OK;
}

STDMETHODIMP CMTParser::loadPlugin(BSTR clsid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	m_excep.clearLastExcep();	
	
	try
	{		
		m_pParser->loadPlugin(clsid);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
		

	return S_OK;
}

STDMETHODIMP CMTParser::loadAllPlugins(BSTR directory, BSTR searchPattern)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		m_pParser->loadAllPlugins(directory, searchPattern);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}


STDMETHODIMP CMTParser::useLocaleSettings()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		
	try
	{
		m_pParser->useLocaleSettings();	
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str(), __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}

STDMETHODIMP CMTParser::setSyntax(SMTSyntax *pSyntax)
{
	

		
	try
	{
		MTSyntax tmpSyntax;
		tmpSyntax.argumentSeparator = pSyntax->argumentSeparator;		
		tmpSyntax.decimalPoint = pSyntax->decimalPoint;
		

		m_pParser->setSyntax(tmpSyntax);	
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}

STDMETHODIMP CMTParser::getSyntax(SMTSyntax *pSyntax)
{
	MTSyntax tmpSyntax;		
	tmpSyntax = m_pParser->getSyntax();			

	pSyntax->argumentSeparator = tmpSyntax.argumentSeparator;		
	pSyntax->decimalPoint = tmpSyntax.decimalPoint;
	

	return S_OK;
}

STDMETHODIMP CMTParser::defineConst(BSTR name, double value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	MTSTRING nameStr = toMTSTRING(name);
	
	try
	{
		m_pParser->defineConst(nameStr.c_str(), value);		
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}


	return S_OK;
}


STDMETHODIMP CMTParser::getParserPtr(int *pParserPtr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	*pParserPtr = (int)m_pParser;

	return S_OK;
}

STDMETHODIMP CMTParser::copy(IMTParser *pParser)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())		
	
	
	int parserPtr;
	pParser->getParserPtr(&parserPtr);
		
	*m_pParser = *((MTParser*)parserPtr);

	return S_OK;
}

STDMETHODIMP CMTParser::getNbUsedVars(int *pNbUsedVars)
{		
	*pNbUsedVars = m_pParser->getNbUsedVars();

	return S_OK;
}

STDMETHODIMP CMTParser::getUsedVar(int index, BSTR *symbol)
{
	try
	{
		*symbol = SysAllocString(m_pParser->getUsedVar(index).c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}	

	return S_OK;
}


STDMETHODIMP CMTParser::getNbDefinedVars(int *pNbDefinedVars)
{		
	*pNbDefinedVars = m_pParser->getNbDefinedVars();

	return S_OK;
}

STDMETHODIMP CMTParser::getVar(int index, BSTR *symbol)
{
	try
	{
		*symbol = SysAllocString(m_pParser->getVar(index)->getSymbol());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}	

	return S_OK;
}

STDMETHODIMP CMTParser::getNbDefinedConsts(int *pNbDefinedConsts)
{	
	*pNbDefinedConsts = m_pParser->getNbDefinedConsts();

	return S_OK;
}

STDMETHODIMP CMTParser::getConst(int index, SMTConstant *pConst)
{
	MTSTRING name;
	MTDOUBLE value;
	try
	{
		m_pParser->getConst(index, name, value);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}

	pConst->name = SysAllocString(name.c_str());
	pConst->value = value;
	pConst->description = SysAllocString(NULL);

	return S_OK;
}

STDMETHODIMP CMTParser::getNbDefinedFuncs(int *pNbDefinedFuncs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pNbDefinedFuncs = m_pParser->getNbDefinedFuncs();

	return S_OK;
}

STDMETHODIMP CMTParser::getFunc(int index, SMTFunction *pFunc)
{
	try
	{
		MTFunctionI *pF = m_pParser->getFunc(index);
		pFunc->ID = SysAllocString(pF->getID());
		pFunc->symbol = SysAllocString(pF->getSymbol());
		pFunc->helpString = SysAllocString(pF->getHelpString());
		pFunc->description = SysAllocString(pF->getDescription());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str(), __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}


STDMETHODIMP CMTParser::getNbDefinedOps(int *pNbDefinedOps)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pNbDefinedOps = m_pParser->getNbDefinedOps();

	return S_OK;
}

STDMETHODIMP CMTParser::getOp(int index, SMTOperator *pOp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		MTOperatorI *pO = m_pParser->getOp(index);
		pOp->ID = SysAllocString(pO->getID());
		pOp->symbol = SysAllocString(pO->getSymbol());
		pOp->helpString = SysAllocString(pO->getHelpString());
		pOp->description = SysAllocString(pO->getDescription());
	
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}



	return S_OK;
}


STDMETHODIMP CMTParser::defineVar(IMTVariable *pVar)
{	
	CComPtr<IMTVariable> varPtr = pVar;	

	if( varPtr == NULL )
	{
		return Error( _T("Invalid variable object (cannot be null)."), __uuidof( IMTParser ), E_FAIL  );
	}	

	MTVariableI *pVarObj;
	int ivarPtr;
	varPtr->getNativeVar(&ivarPtr);
	pVarObj = (MTVariableI*)ivarPtr;
	
	try
	{
		m_pParser->defineVar(pVarObj->spawn());		
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}

	return S_OK;
}

STDMETHODIMP CMTParser::redefineVar(IMTVariable* pVar)
{
	CComPtr<IMTVariable> varPtr = pVar;	

	if( varPtr == NULL )
	{
		return Error( _T("Invalid variable object (cannot be null)."), __uuidof( IMTParser ), E_FAIL  );
	}	

	MTVariableI *pVarObj;
	int ivarPtr;
	varPtr->getNativeVar(&ivarPtr);
	pVarObj = (MTVariableI*)ivarPtr;
	
	try
	{
		m_pParser->redefineVar(pVarObj->spawn());		
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}	

	return S_OK;
}


STDMETHODIMP CMTParser::getNaN(double *pNaN)
{
	*pNaN = m_pParser->getNaN();
	return S_OK;
}

STDMETHODIMP CMTParser::isFinite(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = m_pParser->isFinite();

	return S_OK;
}

STDMETHODIMP CMTParser::isNaN(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = m_pParser->isNaN();

	return S_OK;
}

STDMETHODIMP CMTParser::defineMacro(BSTR prototype, BSTR macro, BSTR description)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	MTSTRING prototypeStr = toMTSTRING(prototype);
	MTSTRING macroStr = toMTSTRING(macro);
	MTSTRING descriptionStr = toMTSTRING(description);
		
	try
	{
		m_pParser->defineMacro(prototypeStr, macroStr, descriptionStr);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );		
	}	

	return S_OK;
}


STDMETHODIMP CMTParser::getLastExcep(IMTExcepData *pExcep)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())	

	m_excep.getLastExcep(pExcep);
	
	return S_OK;
}

MTSTRING CMTParser::toMTSTRING(BSTR &bstr)
{	
	if( bstr != NULL )
	{		
		MTSTRING str;
		str = bstr;
		return str;				
	}
	else
	{
		return _T("");
	}			
	
}

STDMETHODIMP CMTParser::evaluateCompiledBatchVB6(int nbLoops, SAFEARRAY ** pResults)
{
	return evaluateCompiledBatch(nbLoops, *pResults);
}

STDMETHODIMP CMTParser::evaluateCompiledBatch(int nbLoops, SAFEARRAY * pResults)
{
	if( pResults->cDims != 1 )
	{
		return Error( _T("EvaluateCompiledBatch: The result array must have one dimension only") , __uuidof( IMTParser ), E_FAIL  );				
	}

	if( pResults->rgsabound[0].cElements < nbLoops )
	{
		return Error( _T("EvaluateCompiledBatch: The result array is too small") , __uuidof( IMTParser ), E_FAIL  );				
	}

	VARTYPE varType;
	if( FAILED(SafeArrayGetVartype(pResults, &varType)) )
	{
		return Error( _T("EvaluateCompiledBatch: Invalid result array") , __uuidof( IMTParser ), E_FAIL  );				
	}
	
	if( varType != VT_R8 )
	{
		return Error( _T("EvaluateCompiledBatch: Invalid result array type.  Must be double") , __uuidof( IMTParser ), E_FAIL  );				
	}

	m_pParser->evaluateBatch(nbLoops, (double*)pResults->pvData);	

	return S_OK;
}


STDMETHODIMP CMTParser::get_expression(BSTR* pVal)
{
	*pVal = SysAllocString(m_pParser->getExpression().c_str());
	return S_OK;
}

STDMETHODIMP CMTParser::put_expression(BSTR newVal)
{
	compile(newVal);
	return S_OK;
}

STDMETHODIMP CMTParser::get_autoVarDefinitionEnabled(SHORT* pVal)
{
	if( m_pParser->isAutoVarDefinitionEnabled() )
	{
		*pVal = 1;
	}
	else
	{
		*pVal = 0;
	}
	
	return S_OK;
}

STDMETHODIMP CMTParser::put_autoVarDefinitionEnabled(SHORT newVal)
{
	if( newVal != 0 )
	{
		m_pParser->enableAutoVarDefinition(true, new LocalVariableFactory());
	}
	else
	{
		m_pParser->enableAutoVarDefinition(false);
	}
	return S_OK;
}

STDMETHODIMP CMTParser::get_syntax(SMTSyntax* pVal)
{
	getSyntax(pVal);	
	return S_OK;
}

STDMETHODIMP CMTParser::putref_syntax(SMTSyntax newVal)
{		
	setSyntax(&newVal);
	return S_OK;
}

STDMETHODIMP CMTParser::undefineConst(BSTR name)
{	
	try
	{
		m_pParser->undefineConst(name);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}

STDMETHODIMP CMTParser::undefineFuncById(BSTR id)
{	
	try
	{
		m_pParser->undefineFuncById(id);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}

STDMETHODIMP CMTParser::undefineOpById(BSTR id)
{	
	try
	{
		m_pParser->undefineOpById(id);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}

STDMETHODIMP CMTParser::undefineFuncsBySymbol(BSTR symbol)
{	
	try
	{
		m_pParser->undefineFuncsBySymbol(symbol);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}


STDMETHODIMP CMTParser::undefineOpsBySymbol(BSTR symbol)
{	
	try
	{
		m_pParser->undefineOpsBySymbol(symbol);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParser ), E_FAIL  );
	}
	

	return S_OK;
}


//***************************************************************
// FunctionWrapper

void CMTParser::FunctionWrapper::init(CComPtr<IMTFunction> &func)
{
	m_pFunc = func;
	BSTR symbol, helpString, description;
	
	func->getSymbol(&symbol);
	func->getHelpString(&helpString);
	func->getDescription(&description);
	
	m_symbol = symbol;
	m_helpString = helpString;
	m_description = description;

	SysFreeString(symbol);
	SysFreeString(helpString);
	SysFreeString(description);
}									  
		
const MTCHAR* CMTParser::FunctionWrapper::getSymbol()
{
	return m_symbol.c_str();
}

const MTCHAR* CMTParser::FunctionWrapper::getHelpString()
{
	return m_helpString.c_str();
}

const MTCHAR* CMTParser::FunctionWrapper::getDescription()
{
	return m_description.c_str();
}

int CMTParser::FunctionWrapper::getNbArgs()
{
	int nbArgs;
	m_pFunc->getNbArgs(&nbArgs);
	return nbArgs;
}

MTDOUBLE CMTParser::FunctionWrapper::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{
	MTDOUBLE result = 0;
	switch(nbArgs)
	{
	case 0:
		m_pFunc->evaluate0(&result);
		break;
	case 1:
		m_pFunc->evaluate1(pArg[0], &result);
		break;
	case 2:
		m_pFunc->evaluate2(pArg[0], pArg[1], &result);
		break;
	case 3:
		m_pFunc->evaluate3(pArg[0], pArg[1], pArg[2], &result);
		break;
	default:
		SAFEARRAY *pSA;
		SAFEARRAYBOUND aDim[1];   
		aDim[0].lLbound = 0;  
		aDim[0].cElements = nbArgs;
		pSA = SafeArrayCreate(VT_R8, 1, aDim);
		for(int t=0; t<nbArgs; t++)
		{
			((double*)pSA->pvData)[t] = pArg[t];
		}
		
		m_pFunc->evaluate(pSA, &result);
		SafeArrayDestroy(pSA);
	}
	
	return result;
}

MTFunctionI* CMTParser::FunctionWrapper::spawn()
{
	FunctionWrapper* pFunc = new FunctionWrapper();
	pFunc->init(m_pFunc);

	return pFunc;
}