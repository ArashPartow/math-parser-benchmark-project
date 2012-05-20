// MTATLExcepData.h : Declaration of the CMTATLExcepData

#pragma once
#include "resource.h"       // main symbols

#include "MTParserCOM.h"
#include "../MTParserLib/MTException.h"


// CMTATLExcepData

class ATL_NO_VTABLE CMTATLExcepData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMTATLExcepData, &CLSID_MTExcepData>,
	public IDispatchImpl<IMTExcepData, &IID_IMTExcepData, &LIBID_MTPARSERCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMTATLExcepData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MTATLEXCEPDATA)


BEGIN_COM_MAP(CMTATLExcepData)
	COM_INTERFACE_ENTRY(IMTExcepData)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(setNativeData)(int pData);
	STDMETHOD(getNativeData)(int* pData);
	STDMETHOD(getID)(BSTR* pID);
	STDMETHOD(getNbArgs)(LONG* nbArgs);
	STDMETHOD(getArgName)(LONG arg, BSTR* pName);
	STDMETHOD(getArgVal)(LONG arg, BSTR* pVal);
	STDMETHOD(getDescription)(BSTR* pDesc);
	STDMETHOD(setDescription)(BSTR desc);

private:

	MTExcepData m_data;
	MTSTRING m_desc;

	
};

OBJECT_ENTRY_AUTO(__uuidof(MTExcepData), CMTATLExcepData)
