// MTParserLocalizer.h : Declaration of the CMTParserLocalizer

#pragma once
#include "resource.h"       // main symbols

#include "MTParserCOM.h"
#include "../MTParserLib/MTParser.h"
#include "MTExcepHelper.h"

// CMTParserLocalizer

class ATL_NO_VTABLE CMTParserLocalizer : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMTParserLocalizer, &CLSID_MTParserLocalizer>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMTParserLocalizer, &IID_IMTParserLocalizer, &LIBID_MTPARSERCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMTParserLocalizer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MTPARSERLOCALIZER)


BEGIN_COM_MAP(CMTParserLocalizer)
	COM_INTERFACE_ENTRY(IMTParserLocalizer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(registerLibrary)(BSTR infoFile);
	STDMETHOD(setLocale)(BSTR locale);
	STDMETHOD(getNbFuncs)(int* pNbFuncs);
	STDMETHOD(getNbOps)(int* pNbOps);
	STDMETHOD(getNbConsts)(int* pNbConsts);	
	STDMETHOD(getFuncInfo)(BSTR ID, SMTSyntax *pSyntax, SMTFunction* pInfo);
	STDMETHOD(getOpInfo)(BSTR ID, SMTOperator* pInfo);
	STDMETHOD(getConstInfo)(BSTR symbol, SMTConstant* pInfo);
	STDMETHOD(formatExcep)(IMTExcepData *pE, BSTR* msg, BSTR *formattedMsg);
	STDMETHOD(registerAllLibraries)(BSTR directory, BSTR searchPattern);
	STDMETHOD(getExcep)(IMTExcepData* pExcepData, BSTR* pMsg);
	STDMETHOD(getLastExcep)(IMTExcepData* pExcep);
	STDMETHOD(get_locale)(BSTR* pVal);
	STDMETHOD(put_locale)(BSTR newVal);

private:

	MTSTRING toMTSTRING(BSTR &bstr);
	MTExcepHelper m_excep;

	
};

OBJECT_ENTRY_AUTO(__uuidof(MTParserLocalizer), CMTParserLocalizer)
