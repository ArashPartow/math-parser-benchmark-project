// MTDateCOMPlugin.cpp : Implementation of CMTDatePlugin

#include "stdafx.h"
#include "MTDateCOMPlugin.h"

#include "..\..\..\MTParserLib\MTParserPublic.h"
#include "ConvFunc.h"
#include "Func.h"


// CMTDatePlugin

CMTDatePlugin::CMTDatePlugin()
{	
	initPlugin();
}

CMTDatePlugin::~CMTDatePlugin()
{
	unsigned int t;
	unsigned int size;

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

void CMTDatePlugin::initPlugin()
{
	m_funcs.push_back(new DateConvFunc());
	m_funcs.push_back(new TimeConvFunc());	

	m_funcs.push_back(new DateFunc());
	m_funcs.push_back(new TimeFunc());
	m_funcs.push_back(new DayFunc());
	m_funcs.push_back(new HourFunc());
	m_funcs.push_back(new MinuteFunc());
	m_funcs.push_back(new SecondFunc());
	m_funcs.push_back(new YearFunc());
	m_funcs.push_back(new MonthFunc());
	m_funcs.push_back(new DayOfWeekFunc());
	m_funcs.push_back(new DayOfYearFunc());
	m_funcs.push_back(new NowDateFunc());
	m_funcs.push_back(new NowTimeFunc());
}

void CMTDatePlugin::addConst(LPCTSTR name, double value)
{
	SConstant constant;
	constant.name = name;
	constant.value = value;

	m_consts.push_back(constant);
}

STDMETHODIMP CMTDatePlugin::getNbConsts(INT *pNbConsts)
{
	*pNbConsts = m_consts.size();
	return S_OK;
}


STDMETHODIMP CMTDatePlugin::getConst(INT id, SMTPluginConst * pConst)
{
	pConst->name = SysAllocString(m_consts[id].name);
	pConst->val = m_consts[id].value;
	return S_OK;
}
STDMETHODIMP CMTDatePlugin::getNbFuncs(INT * pNbFuncs)
{
	*pNbFuncs = m_funcs.size();
	return S_OK;
}
STDMETHODIMP CMTDatePlugin::newFunc(INT id, int * pFunc)
{
	*pFunc = (int)m_funcs[id]->spawn();
	
	return S_OK;
}

STDMETHODIMP CMTDatePlugin::getNbOps(INT * pNbOps)
{
	*pNbOps = m_ops.size();
	return S_OK;
}
STDMETHODIMP CMTDatePlugin::newOp(INT id, int * pOp)
{
	*pOp = (int)m_ops[id]->spawn();
	
	return S_OK;
}

STDMETHODIMP CMTDatePlugin::getMTParserVersion(BSTR * pVersion)
{
	*pVersion = SysAllocString(MTSTRINGTOUNICODE(MTPARSER_INTERFACE_VERSION));
	return S_OK;
}

STDMETHODIMP CMTDatePlugin::getInfoFile(BSTR * pInfoFile, BSTR *pVersion, int *pIsAvailable)
{
	*pInfoFile = SysAllocString(MTSTRINGTOUNICODE(_T("MTDatePlugin.xml")));
	*pVersion = SysAllocString(MTSTRINGTOUNICODE(_T("1")));
	*pIsAvailable = 1;
	return S_OK;
}


