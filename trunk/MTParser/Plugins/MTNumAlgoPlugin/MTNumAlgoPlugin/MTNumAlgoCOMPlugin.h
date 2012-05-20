// MTNumAlgoCOMPlugin.h : Declaration of the CMTNumAlgoPlugin

#pragma once
#include "resource.h"       // main symbols
#include <vector>

// IMTNumAlgoPlugin
[
	object,
	uuid("E47FB6D5-A248-48F5-885E-214702CE6A20"),
	dual,	helpstring("IMTNumAlgoPlugin Interface"),
	pointer_default(unique)
]
__interface IMTNumAlgoPlugin : IDispatch
{
};



// CMTNumAlgoPlugin

[
	coclass,
	threading("free"),
	support_error_info("IMTNumAlgoPlugin"),
	vi_progid("MTNumAlgoPlugin.MTNumAlgoPlugin"),
	progid("MTNumAlgoPlugin.MTNumAlgoPlugin.1"),
	version(1.0),
	uuid("1F6C2D74-1023-4E0F-8A6B-DBA19E6585E3"),
	helpstring("MTNumAlgoPlugin Class")
]
class ATL_NO_VTABLE CMTNumAlgoPlugin : 
	public IMTNumAlgoPlugin,
	public IDispatchImpl<IMTParserPlugin, &__uuidof(IMTParserPlugin), &LIBID_MTParserPlugin, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CMTNumAlgoPlugin();
	~CMTNumAlgoPlugin();

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

private:

	std::vector<class MTFunctionI*> m_funcs;
	std::vector<class MTOperatorI*> m_ops;
};

