// MTDateCOMPlugin.h : Declaration of the CMTDatePlugin

#pragma once
#include "resource.h"       // main symbols
#include <vector>

// IMTDatePlugin
[
	object,
	uuid("AF39D9F5-EF4F-4356-B035-0A58AD12579F"),
	dual,	helpstring("IMTDatePlugin Interface"),
	pointer_default(unique)
]
__interface IMTDatePlugin : IDispatch
{
};



// CMTDatePlugin

[
	coclass,
	threading("free"),
	support_error_info("IMTDatePlugin"),
	vi_progid("MTDatePlugin.MTDatePlugin"),
	progid("MTDatePlugin.MTDatePlugin.1"),
	version(1.0),
	uuid("43F6302F-94FD-4702-908D-EA1F157080AD"),
	helpstring("MTDatePlugin Class")
]
class ATL_NO_VTABLE CMTDatePlugin : 
	public IMTDatePlugin,
	public IDispatchImpl<IMTParserPlugin, &__uuidof(IMTParserPlugin), &LIBID_MTParserPlugin, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CMTDatePlugin();
	~CMTDatePlugin();
	
	


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

public:


	// IMTParserPlugin Methods
public:

	STDMETHOD(getNbConsts)(INT * pNbConsts);
	STDMETHOD(getConst)(INT id, SMTPluginConst * pConst);
	STDMETHOD(getNbFuncs)(INT * pNbFuncs);
	STDMETHOD(newFunc)(INT id, int * pFunc);	
	STDMETHOD(getNbOps)(INT * pNbOps);
	STDMETHOD(newOp)(INT id, int * pOp);		
	STDMETHOD(getMTParserVersion)(BSTR * pVersion);		
	STDMETHOD(getInfoFile)(BSTR * pInfoFile, BSTR *pVersion, int *pIsAvailable);		

private:

	// create function and operator objects
	void initPlugin();

	// add a constant
	void addConst(LPCTSTR name, double value);

private:

	struct SConstant
	{
		CComBSTR name;
		double value;
	};

	std::vector<class MTFunctionI*> m_funcs;
	std::vector<class MTOperatorI*> m_ops;
	std::vector<SConstant> m_consts;

	
};

