// MTParserPluginIDL.h : Declaration of the CMTParserPlugin

#pragma once
#include "resource.h"       // main symbols

[export, library_block]
[uuid("9D7C0E14-9312-3884-9F47-BFCFA847AFCF")]
struct SMTPluginConst
{
	BSTR name;
	double val;
};

// IMTParserPlugin
[
	object,
	uuid("91893C09-F41E-4389-9185-42B2E0D5A49E"),
	dual,	helpstring("IMTParserPlugin Interface"),
	pointer_default(unique)
]
__interface IMTParserPlugin : IDispatch
{
	[id(1), helpstring("Return the number of constants")] HRESULT getNbConsts([out, retval] int *pNbConsts);
	[id(2), helpstring("Return the information about a constant")] HRESULT getConst([in] int constID, [out, retval] SMTPluginConst *pConst);

	[id(3), helpstring("Return the number of functions")] HRESULT getNbFuncs([out, retval] int *pNbFuncs);
	[id(4), helpstring("Create a new function's object")] HRESULT newFunc([in] int funcID, [out, retval] int *pFunc);

	[id(5), helpstring("Return the number of operators")] HRESULT getNbOps([out, retval] int *pNbOps);
	[id(6), helpstring("Create a new operator's object")] HRESULT newOp([in] int opID, [out, retval] int *pOp);			
	[id(7), helpstring("Return the compatible MTParser library's interface")] HRESULT getMTParserVersion([out, retval] BSTR *pVersion);

	[id(8), helpstring("Return the info file and the compatible version")] HRESULT getInfoFile([out] BSTR *pInfoFile, [out] BSTR *pVersion, [out, retval] int *pIsAvailable);
};



// CMTParserPlugin

[
	coclass,
	threading("free"),
	vi_progid("MTParserPlugin.MTParserPlugin"),
	progid("MTParserPlugin.MTParserPlugin.1"),
	version(1.0),
	uuid("99DA618B-2DA5-444C-AEA2-195C02F11F5A"),
	helpstring("MTParserPlugin Class")
]
class ATL_NO_VTABLE CMTParserPlugin : 
	public IMTParserPlugin
{
public:
	CMTParserPlugin()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(getNbConsts)(INT * pNbConsts);
	STDMETHOD(getConst)(INT id, SMTPluginConst * pConst);
	STDMETHOD(getNbFuncs)(INT * pNbFuncs);
	STDMETHOD(newFunc)(INT id, int * pFunc);	
	STDMETHOD(getNbOps)(INT * pNbOps);
	STDMETHOD(newOp)(INT id, int * pOp);		
	STDMETHOD(getMTParserVersion)(BSTR * pVersion);		
	STDMETHOD(getInfoFile)(BSTR * pInfoFile, BSTR *pVersion, int *pIsAvailable);

};

