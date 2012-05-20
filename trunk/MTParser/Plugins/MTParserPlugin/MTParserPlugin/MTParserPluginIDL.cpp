// MTParserPluginIDL.cpp : Implementation of CMTParserPlugin

#include "stdafx.h"
#include "MTParserPluginIDL.h"


// CMTParserPlugin

STDMETHODIMP CMTParserPlugin::getNbConsts(INT *pNbConsts)
{
	*pNbConsts = 0;
	return S_OK;
}


STDMETHODIMP CMTParserPlugin::getConst(INT id, SMTPluginConst * pConst)
{		
	return S_OK;
}
STDMETHODIMP CMTParserPlugin::getNbFuncs(INT * pNbFuncs)
{
	*pNbFuncs = 0;
	return S_OK;
}
STDMETHODIMP CMTParserPlugin::newFunc(INT id, int * pFunc)
{
	*pFunc = 0;
	
	return S_OK;
}

STDMETHODIMP CMTParserPlugin::getNbOps(INT * pNbOps)
{
	*pNbOps = 0;
	return S_OK;
}
STDMETHODIMP CMTParserPlugin::newOp(INT id, int * pOp)
{
	*pOp = 0;
	
	return S_OK;
}

STDMETHODIMP CMTParserPlugin::getMTParserVersion(BSTR * pVersion)
{
	*pVersion = 0;
	return S_OK;
}

STDMETHODIMP CMTParserPlugin::getInfoFile(BSTR * pInfoFile, BSTR *pVersion, int *pIsAvailable)
{
	*pInfoFile = 0;
	*pVersion = 0;
	*pIsAvailable = 0;
	return S_OK;
}


