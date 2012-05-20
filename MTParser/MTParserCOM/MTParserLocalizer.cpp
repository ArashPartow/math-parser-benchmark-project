// MTParserLocalizer.cpp : Implementation of CMTParserLocalizer

#include "stdafx.h"
#include "MTParserLocalizer.h"
#include "../MTParserLib/MTParserLocalizer.h"
#include "../MTParserLib/MTParserExcepStrEng.h"

// CMTParserLocalizer

STDMETHODIMP CMTParserLocalizer::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMTParserLocalizer
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMTParserLocalizer::registerLibrary(BSTR infoFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		MTParserLocalizer::getInstance()->registerLibrary(toMTSTRING(infoFile).c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}
	

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::setLocale(BSTR locale)
{

	try
	{
		MTParserLocalizer::getInstance()->setLocale(toMTSTRING(locale).c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::get_locale(BSTR* pVal)
{
	MTSTRING locale = MTParserLocalizer::getInstance()->getLocale();
	*pVal = SysAllocString(locale.c_str());	
	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::put_locale(BSTR newVal)
{
	setLocale(newVal);
	return S_OK;
}


STDMETHODIMP CMTParserLocalizer::getNbFuncs(int* pNbFuncs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pNbFuncs = MTParserLocalizer::getInstance()->getNbFuncs();

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getNbOps(int* pNbOps)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pNbOps = MTParserLocalizer::getInstance()->getNbOps();

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getNbConsts(int* pNbConsts)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pNbConsts = MTParserLocalizer::getInstance()->getNbConsts();

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getFuncInfo(BSTR ID, SMTSyntax *pSyntax, SMTFunction* pInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MTParserLocalizer::SFuncInfo info;
	try
	{
		info = MTParserLocalizer::getInstance()->getFuncInfo(toMTSTRING(ID).c_str());

		pInfo->ID = SysAllocString(ID);		
		pInfo->symbol = SysAllocString(info.symbol.c_str());		
		
		MTSyntax tmpSyntax;
		tmpSyntax.argumentSeparator = pSyntax->argumentSeparator;		
		tmpSyntax.decimalPoint = pSyntax->decimalPoint;
		
		pInfo->helpString = SysAllocString(MTParserLocalizer::formatFuncPrototype(info, tmpSyntax).c_str());

		pInfo->description = SysAllocString(info.desc.c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}	
	

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getOpInfo(BSTR ID, SMTOperator* pInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MTParserLocalizer::SOpInfo info;
	try
	{
		info = MTParserLocalizer::getInstance()->getOpInfo(toMTSTRING(ID).c_str());

		pInfo->ID = SysAllocString(ID);		
		pInfo->symbol = SysAllocString(info.symbol.c_str());				
		pInfo->helpString = SysAllocString(MTParserLocalizer::formatOpPrototype(info).c_str());
		pInfo->description = SysAllocString(info.desc.c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getConstInfo(BSTR symbol, SMTConstant* pInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MTParserLocalizer::SConstInfo info;
	try
	{
		info = MTParserLocalizer::getInstance()->getConstInfo(toMTSTRING(symbol).c_str());
		
		pInfo->name = SysAllocString(info.symbol.c_str());			
		pInfo->description = SysAllocString(info.desc.c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}


	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::formatExcep(IMTExcepData *pE, BSTR* msg, BSTR *formattedMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int pData;
	pE->getNativeData(&pData);
	
	*formattedMsg = SysAllocString(MTParserExcepStrEng::format(*((MTExcepData*)pData), toMTSTRING(*msg).c_str()).c_str());

	return S_OK;
}

MTSTRING CMTParserLocalizer::toMTSTRING(BSTR &bstr)
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


STDMETHODIMP CMTParserLocalizer::registerAllLibraries(BSTR directory, BSTR searchPattern)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		MTParserLocalizer::getInstance()->registerAllLibraries(directory, searchPattern);
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getExcep(IMTExcepData* pExcepData, BSTR* pMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		int pData;
		pExcepData->getNativeData(&pData);	
		
		*pMsg = SysAllocString(MTParserLocalizer::getInstance()->getExcep(*((MTExcepData*)pData)).c_str());
	}
	catch( MTParserException &e )
	{
		m_excep.setLastExcep(e);
		return Error( MTExcepHelper::getAllExceptionString(e).c_str() , __uuidof( IMTParserLocalizer ), E_FAIL  );		
	}

	return S_OK;
}

STDMETHODIMP CMTParserLocalizer::getLastExcep(IMTExcepData* pExcep)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_excep.getLastExcep(pExcep);

	return S_OK;
}

