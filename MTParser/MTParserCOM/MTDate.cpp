// MTDate.cpp : Implementation of CMTDate
#include "stdafx.h"
#include "MTParserCOM.h"
#include "MTDate.h"
#include <math.h>
#include ".\mtdate.h"
#include "../MTParserLib/MTTools.h"

/////////////////////////////////////////////////////////////////////////////
// CMTDate

STDMETHODIMP CMTDate::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMTDate
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CMTDate::CMTDate()
{
	m_pUnkMarshaler = NULL;
	m_isCreated = false;		
}

STDMETHODIMP CMTDate::getName(BSTR *pName)
{
	if( !m_isCreated )
	{
		return Error( _T("Variable not created yet.  Call the create method first."), __uuidof( IMTDouble ), E_FAIL  );
	}
	
	*pName = SysAllocString(m_name);

	return S_OK;
}

STDMETHODIMP CMTDate::setValue(DOUBLE value)
{
	m_dt = value;
	return S_OK;
}

STDMETHODIMP CMTDate::getValue(DOUBLE * pValue)
{
	if( m_dt.m_status == COleDateTime::valid )
	{
		*pValue = m_dt.m_dt;
	}
	else
	{
		*pValue = MTTools::NaN;		
	}

	return S_OK;
}

STDMETHODIMP CMTDate::create(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( m_isCreated )
	{
		return Error( _T("Variable already created.  Cannot create it twice."), __uuidof( IMTDate ), E_FAIL  );
	}
	
	m_name = name;	
	m_isCreated = true;	

	return S_OK;
}

STDMETHODIMP CMTDate::parseDateTime(BSTR datetime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())	
	
	m_dt.ParseDateTime(datetime);	

	if( m_dt.m_status != COleDateTime::valid )
	{
		return Error( _T("Invalid date/time format"), __uuidof( IMTDate ), E_FAIL  );
	}	

	return S_OK;
}


STDMETHODIMP CMTDate::setDate(int year, int month, int day)
{	
	m_dt.SetDate(year, month, day);
	return S_OK;
}

STDMETHODIMP CMTDate::setTime(int hour, int minute, int second)
{
	m_dt.SetTime(hour, minute, second);	
	return S_OK;
}

STDMETHODIMP CMTDate::get_name(BSTR *pVal)
{
	*pVal = SysAllocString(m_name);
	return S_OK;
}

STDMETHODIMP CMTDate::get_value(double *pVal)
{	
	getValue(pVal);
	return S_OK;
}

STDMETHODIMP CMTDate::put_value(double newVal)
{
	m_dt = newVal;
	return S_OK;
}

STDMETHODIMP CMTDate::format(BSTR *pDateStr)
{
	*pDateStr = SysAllocString(m_dt.Format());
	return S_OK;
}


STDMETHODIMP CMTDate::getNativeVar(int* pVar)
{
	*pVar = (int)&m_var;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// MTDoubleAdapter

void CMTDate::MTDateAdapter::init(CComPtr<IMTDate> &pVar)
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

const MTCHAR* CMTDate::MTDateAdapter::getSymbol()
{
	return m_name.c_str();
}

MTVariableI* CMTDate::MTDateAdapter::spawn()
{
	MTDateAdapter *pVar = new MTDateAdapter();

	pVar->init(m_pVar);
	return pVar;

}

MTDOUBLE CMTDate::MTDateAdapter::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{	
	double val;
	m_pVar->getValue(&val);
	return val;
}

