// MTDouble.cpp : Implementation of CMTDouble
#include "stdafx.h"
#include "MTParserCOM.h"
#include "MTDouble.h"
#include ".\mtdouble.h"

/////////////////////////////////////////////////////////////////////////////
// CMTDouble

STDMETHODIMP CMTDouble::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMTDouble
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CMTDouble::CMTDouble()
{
	m_pUnkMarshaler = NULL;
	m_isCreated = false;
	m_value = 0;
}

STDMETHODIMP CMTDouble::getName(BSTR *pName)
{
	if( !m_isCreated )
	{
		return Error( _T("Variable not created yet.  Call the create method first."), __uuidof( IMTDouble ), E_FAIL  );
	}
	
	*pName = SysAllocString(m_name);



	return S_OK;
}

STDMETHODIMP CMTDouble::setValue(DOUBLE value)
{
	m_value = value;	
	return S_OK;
}

STDMETHODIMP CMTDouble::getValue(DOUBLE * pValue)
{
	*pValue = m_value;
	return S_OK;
}

STDMETHODIMP CMTDouble::create(BSTR name, double value)
{
	if( m_isCreated )
	{
		return Error( _T("Variable already created.  Cannot create it twice."), __uuidof( IMTDouble ), E_FAIL  );
	}
	
	m_name = name;
	m_value = value;
	m_isCreated = true;
	
	CComPtr<IMTDouble> varPtr = this;	
	m_var.init(varPtr);

	return S_OK;
}

STDMETHODIMP CMTDouble::get_value(double *pVal)
{
	*pVal = m_value;
	return S_OK;
}

STDMETHODIMP CMTDouble::put_value(double newVal)
{
	m_value = newVal;
	return S_OK;
}

STDMETHODIMP CMTDouble::get_name(BSTR *pVal)
{
	*pVal = SysAllocString(m_name);
	return S_OK;
}


STDMETHODIMP CMTDouble::getNativeVar(int* pVar)
{
	*pVar = (int)&m_var;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// MTDoubleAdapter

void CMTDouble::MTDoubleAdapter::init(CComPtr<IMTDouble> &pVar)
{
	m_pVar = pVar;
	BSTR name;
	IMTVariable *pBaseVar;
	m_pVar->QueryInterface(__uuidof(IMTVariable), (void**)&pBaseVar);

	pBaseVar->getName(&name);
	pBaseVar->Release();

	m_name = name;
	SysFreeString(name);
}

const MTCHAR* CMTDouble::MTDoubleAdapter::getSymbol()
{
	return m_name.c_str();
}

MTVariableI* CMTDouble::MTDoubleAdapter::spawn()
{
	MTDoubleAdapter *pVar = new MTDoubleAdapter();

	pVar->init(m_pVar);
	return pVar;

}

MTDOUBLE CMTDouble::MTDoubleAdapter::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{	
	double val;
	m_pVar->getValue(&val);
	return val;
}

