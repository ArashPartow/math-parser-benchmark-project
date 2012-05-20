// MTATLExcepData.cpp : Implementation of CMTATLExcepData

#include "stdafx.h"
#include "MTATLExcepData.h"
#include ".\mtatlexcepdata.h"


// CMTATLExcepData


STDMETHODIMP CMTATLExcepData::setNativeData(int pData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_data = *((MTExcepData*)pData);

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getNativeData(int* pData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pData = (int)&m_data;

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getID(BSTR* pID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pID = SysAllocString(m_data.getID());

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getNbArgs(LONG* nbArgs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*nbArgs = m_data.getNbArgs();

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getArgName(LONG arg, BSTR* pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pName = SysAllocString(m_data.getArgName(arg));

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getArgVal(LONG arg, BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = SysAllocString(m_data.getArgVal(arg));

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::getDescription(BSTR* pDesc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pDesc = SysAllocString(m_desc.c_str());

	return S_OK;
}

STDMETHODIMP CMTATLExcepData::setDescription(BSTR desc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_desc = UNICODETOMTSTRING(desc);

	return S_OK;
}
