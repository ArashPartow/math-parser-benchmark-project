// MTDoubleVector.cpp : Implementation of CMTDoubleVector

#include "stdafx.h"
#include "MTDoubleVector.h"
#include ".\mtdoublevector.h"
#include "../MTParserLib/MTTools.h"

// CMTDoubleVector

STDMETHODIMP CMTDoubleVector::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMTDoubleVector
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMTDoubleVector::getName(BSTR *pName)
{
	if( !m_isCreated )
	{
		return Error( _T("Variable not created yet.  Call the create method first."), __uuidof( IMTDoubleVector ), E_FAIL  );
	}
	
	*pName = SysAllocString(m_name);

	return S_OK;
}

CMTDoubleVector::CMTDoubleVector()
{
	m_pValues = NULL;
	m_nbValues = 0;
	m_isCreated = false;
}

CMTDoubleVector::~CMTDoubleVector()
{
	clear();
}

void CMTDoubleVector::clear()
{
	if( m_pValues != NULL )
	{
		delete []m_pValues;
		m_pValues = NULL;
	}
}

STDMETHODIMP CMTDoubleVector::setValueVectorVB6(SAFEARRAY ** pValues)
{
	return setValueVector(*pValues);
}

STDMETHODIMP CMTDoubleVector::setValueVector(SAFEARRAY * pValues)
{

	VARTYPE varType;
	if( FAILED(SafeArrayGetVartype(pValues, &varType)) )
	{
		return Error( _T("setValueVector: Invalid result array") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}
	
	if( varType != VT_R8 )
	{
		return Error( _T("setValueVector: Invalid result array type.  Must be double") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}

	if( (pValues)->cDims != 1 )
	{
		return Error( _T("setValueVector: The array must have only one dimension") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}

	clear();	
	m_nbValues = pValues->rgsabound[0].cElements;	
	m_pValues = new double[m_nbValues];
	CopyMemory(m_pValues, pValues->pvData, sizeof(double)*m_nbValues);	
	
	updateListeners();
	return S_OK;
}


STDMETHODIMP CMTDoubleVector::create(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_name = name;
	m_isCreated = true;
	CComPtr<IMTDoubleVector> varPtr = this;	
	m_var.init(varPtr);

	return S_OK;
}


STDMETHODIMP CMTDoubleVector::getNativeVar(int* pVar)
{
	*pVar = (int)&m_var;
	return S_OK;
}

STDMETHODIMP CMTDoubleVector::registerListener(int pListener)
{
	m_varListeners.push_back((MTDoubleVectorAdapter*)pListener);
	return S_OK;
}

STDMETHODIMP CMTDoubleVector::unregisterListener(int pListener)
{
	// find the listener and remove it
	for(unsigned int t=0; t<m_varListeners.size(); t++ )
	{
		if( m_varListeners[t] == (MTDoubleVectorAdapter*)pListener )
		{
			m_varListeners.erase(m_varListeners.begin()+t);
		}
	}

	return S_OK;
}

void CMTDoubleVector::updateListeners()
{
	for(unsigned int t=0; t<m_varListeners.size(); t++ )
	{
		m_varListeners[t]->setValues(m_pValues, m_nbValues);		
	}	
}

/////////////////////////////////////////////////////////////////////////////
// MTDoubleVectorAdapter

MTDOUBLE CMTDoubleVector::MTDoubleVectorAdapter::m_nanValue = MTTools::generateNaN();

void CMTDoubleVector::MTDoubleVectorAdapter::init(CComPtr<IMTDoubleVector> &pVar)
{
	m_pVar = pVar;
	BSTR name;
	IMTVariable *pBaseVar;
	m_pVar->QueryInterface(__uuidof(IMTVariable), (void**)&pBaseVar);

	pBaseVar->getName(&name);
	pBaseVar->Release();

	m_name = name;
	SysFreeString(name);

	m_pVar->registerListener((int)this);
}

CMTDoubleVector::MTDoubleVectorAdapter::MTDoubleVectorAdapter()
{
	m_pVar = NULL;
}

CMTDoubleVector::MTDoubleVectorAdapter::~MTDoubleVectorAdapter()
{
	if( m_pVar != NULL )
	{
		m_pVar->unregisterListener((int)this);
	}
}


void CMTDoubleVector::MTDoubleVectorAdapter::setValues(MTDOUBLE *pValues, unsigned int nbValues)
{
	if( nbValues == 0 )
	{
		nbValues = 1;
		pValues = &m_nanValue;
	}
	
	m_pValues = pValues;
	m_nbValues = nbValues;
	m_pos = 0;	
}

const MTCHAR* CMTDoubleVector::MTDoubleVectorAdapter::getSymbol()
{
	return m_name.c_str();
}

MTVariableI* CMTDoubleVector::MTDoubleVectorAdapter::spawn()
{
	MTDoubleVectorAdapter *pVar = new MTDoubleVectorAdapter();

	pVar->init(m_pVar);
	pVar->setValues(m_pValues, m_nbValues);
	return pVar;

}

MTDOUBLE CMTDoubleVector::MTDoubleVectorAdapter::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{	
	MTDOUBLE val = m_pValues[m_pos];
	m_pos = (m_pos+1)%m_nbValues;
	return val;
}


