// MTNumAlgoCOMPlugin.cpp : Implementation of CMTNumAlgoPlugin

#include "stdafx.h"
#include "MTNumAlgoCOMPlugin.h"
#include "Funcs.h"

// CMTNumAlgoPlugin

CMTNumAlgoPlugin::CMTNumAlgoPlugin()
{	
	initPlugin();
}

CMTNumAlgoPlugin::~CMTNumAlgoPlugin()
{
	int t;
	int size;

	// delete all functions
	size = m_funcs.size();
	for( t=0; t<size; t++ )
	{
		delete m_funcs[t];
	}

	// delete all operators
	size = m_ops.size();
	for( t=0; t<size; t++ )
	{
		delete m_ops[t];
	}	

}

void CMTNumAlgoPlugin::initPlugin()
{
	m_funcs.push_back(new DerivativeFct());
	m_funcs.push_back(new TrapezoidFct());	
	m_funcs.push_back(new SolveFct());	
}

STDMETHODIMP CMTNumAlgoPlugin::getNbConsts(INT *pNbConsts)
{
	*pNbConsts = 0;
	return S_OK;
}


STDMETHODIMP CMTNumAlgoPlugin::getConst(INT id, SMTPluginConst * pConst)
{	
	return E_FAIL;
}
STDMETHODIMP CMTNumAlgoPlugin::getNbFuncs(INT * pNbFuncs)
{
	*pNbFuncs = m_funcs.size();
	return S_OK;
}
STDMETHODIMP CMTNumAlgoPlugin::newFunc(INT id, int * pFunc)
{
	*pFunc = (int)m_funcs[id]->spawn();
	
	return S_OK;
}

STDMETHODIMP CMTNumAlgoPlugin::getNbOps(INT * pNbOps)
{
	*pNbOps = m_ops.size();
	return S_OK;
}
STDMETHODIMP CMTNumAlgoPlugin::newOp(INT id, int * pOp)
{
	*pOp = (int)m_ops[id]->spawn();
	
	return S_OK;
}

STDMETHODIMP CMTNumAlgoPlugin::getMTParserVersion(BSTR * pVersion)
{
	*pVersion = SysAllocString(MTSTRINGTOUNICODE(MTPARSER_INTERFACE_VERSION));
	return S_OK;
}

STDMETHODIMP CMTNumAlgoPlugin::getInfoFile(BSTR * pInfoFile, BSTR *pVersion, int *pIsAvailable)
{
	*pInfoFile = SysAllocString(MTSTRINGTOUNICODE(_T("MTNumAlgoPlugin.xml")));
	*pVersion = SysAllocString(MTSTRINGTOUNICODE((_T("1"))));
	*pIsAvailable = 1;
	return S_OK;
}


