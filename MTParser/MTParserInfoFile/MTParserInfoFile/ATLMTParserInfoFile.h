// ATLMTParserInfoFile.h : Declaration of the CATLMTParserInfoFile

#pragma once
#include "resource.h"       // main symbols
#using <mscorlib.dll>
#using <System.Xml.dll>
#include <string>
#include <vector>

[export, library_block]
[uuid("9D7C0E15-9513-4884-9F47-BFCFA847AFCF")]
struct SATLFuncInfo {
	[helpstring("Function's identifier")]			BSTR id;
	[helpstring("Function's symbol")]				BSTR symbol;
	[helpstring("Function's arguments")]			BSTR args;
	[helpstring("Function argument descriptions")]  BSTR argDescs;
	[helpstring("Function's description")]			BSTR desc;    
};

[export, library_block]
[uuid("9D7C0E14-9513-4884-9F47-BFCFA847AFCF")]
struct SATLOpInfo {
	[helpstring("Operator's identifier")]			BSTR id;
    [helpstring("Operator's symbol")]				BSTR symbol;
	[helpstring("Operator's arguments")]			BSTR args;	
	[helpstring("Operator's description")]			BSTR desc;  
    
};

[export, library_block]
[uuid("9D7C0E13-9513-4884-9F47-BFCFA847AFCF")]
struct SATLConstInfo {
    [helpstring("Constant's name")]					BSTR symbol;
	[helpstring("Constant's description")]			BSTR desc;
    
};

[export, library_block]
[uuid("9D7C0E12-9512-4884-9F47-BFCFA847AFCF")]
struct SATLVarInfo {
    [helpstring("Variable's name")]					BSTR symbol;
	[helpstring("Variable's description")]			BSTR desc;
    
};

[export, library_block]
[uuid("9D7C0E12-9512-4884-9F47-BFAFB846AFCF")]
struct SATLExcepInfo {
    [helpstring("Exception's id")]					BSTR id;
	[helpstring("Exception's description")]			BSTR desc;
    
};

[export, library_block]
[uuid("9D7C0E11-9512-4884-9F47-BFCFA847AFCF")]
struct SATLLibInfo {
    [helpstring("Library's title")]					BSTR title;
	[helpstring("Library's description")]			BSTR desc;
	[helpstring("Library's compatible version")]    BSTR version;
	[helpstring("Library's type")]					BSTR type;
	[helpstring("Data1")]							BSTR data1;
	[helpstring("Data2")]							BSTR data2;   
};


// IMTParserInfoFile
[
	object,
	uuid("9D7C0E16-9513-4884-9F47-BFCFA847AFCF"),
	dual,	helpstring("IMTParserInfoFile Interface"),
	pointer_default(unique)
]
__interface IMTParserInfoFile : IDispatch
{	
	[id(1), helpstring("method load")] HRESULT load([in] BSTR fileName);
	[id(2), helpstring("method getNbLocales")] HRESULT getNbLocales([out,retval] ULONG* pNbLocales);
	[id(3), helpstring("method getLocale")] HRESULT getLocale([in] ULONG id, [out,retval] BSTR* pLocale);
	[id(4), helpstring("method setLocale")] HRESULT setLocale([in] BSTR locale);
	[id(5), helpstring("method getNbFuncs")] HRESULT getNbFuncs([out,retval] ULONG* pNbFuncs);
	[id(6), helpstring("method getFunc")] HRESULT getFunc([in] ULONG id, [out,retval] SATLFuncInfo* pFunc);
	[id(7), helpstring("method getOp")] HRESULT getOp([in] ULONG id, [out,retval] SATLOpInfo* pOp);
	[id(8), helpstring("method getConst")] HRESULT getConst([in] ULONG id, [out,retval] SATLConstInfo* pConst);
	[id(9), helpstring("method getVar")] HRESULT getVar([in] ULONG id, [out,retval] SATLVarInfo* pVar);
	[id(10), helpstring("method getLibInfo")] HRESULT getLib([out,retval] SATLLibInfo* pLib);
	[id(11), helpstring("method getNbOps")] HRESULT getNbOps([out,retval] ULONG* pNbOps);
	[id(12), helpstring("method getNbConsts")] HRESULT getNbConsts([out,retval] ULONG* pNbConsts);
	[id(13), helpstring("method getNbVars")] HRESULT getNbVars([out,retval] ULONG* pNbVars);
	[id(14), helpstring("method getNbExceps")] HRESULT getNbExceps([out,retval] ULONG* pNbExceps);
	[id(15), helpstring("method getExcep")] HRESULT getExcep([in] ULONG id, [out,retval] SATLExcepInfo* pExcep);
};



// CATLMTParserInfoFile

[
	coclass,
	threading("free"),
	support_error_info("IMTParserInfoFile"),
	vi_progid("MTParserInfoFile.MTParserInfoFile"),
	progid("MTParserInfoFile.MTParserInfoFile.1"),
	version(1.0),
	uuid("B521F2A0-5D67-4164-A04B-32D636DB8F9F"),
	helpstring("MTParserInfoFile Class")
]
class ATL_NO_VTABLE CATLMTParserInfoFile : 
	public IMTParserInfoFile
{
public:
	CATLMTParserInfoFile()
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

	STDMETHOD(load)(BSTR fileName);
	STDMETHOD(getNbLocales)(ULONG* pNbLocales);
	STDMETHOD(getLocale)(ULONG id, BSTR* pLocale);
	STDMETHOD(setLocale)(BSTR locale);
	STDMETHOD(getNbFuncs)(ULONG* pNbFuncs);
	STDMETHOD(getFunc)(ULONG id, SATLFuncInfo* pFunc);
	STDMETHOD(getOp)(ULONG id, SATLOpInfo* pOp);
	STDMETHOD(getConst)(ULONG id, SATLConstInfo* pConst);
	STDMETHOD(getVar)(ULONG id, SATLVarInfo* pVar);
	STDMETHOD(getExcep)(ULONG id, SATLExcepInfo* pVar);
	STDMETHOD(getLib)(SATLLibInfo* pLib);
	STDMETHOD(getNbOps)(ULONG* pNbOps);
	STDMETHOD(getNbConsts)(ULONG* pNbConsts);
	STDMETHOD(getNbVars)(ULONG* pNbVars);
	STDMETHOD(getNbExceps)(ULONG* pNbExceps);

private:

	/** @brief Convert a managed string to a stl string
	@param	pStr	Managed string
	@return a stl string
	*/
	std::wstring convMngString(System::String *pStr);
	
	/** @brief Find the function position 
	@param	id	Function's string id
	@return the function position in the function's list
	*/
	unsigned int findFunc(BSTR id);
	
	/** @brief Find the operator position 
	@param	id	Operator's string id
	@return the operator position in the operator's list
	*/
	unsigned int findOp(BSTR id);

	std::wstring m_xmlFile;						// xml filename

	std::wstring m_fileName;	
	std::vector<std::wstring> m_localeList;		// list of all locales	

	struct sFuncInfo
	{		
		std::wstring id;
		std::wstring symbol;
		std::wstring args;
		std::wstring argDescs;
		std::wstring desc;
	};

	struct sOpInfo
	{		
		std::wstring id;
		std::wstring symbol;
		std::wstring args;
		std::wstring desc;
	};

	struct sConstInfo
	{		
		std::wstring symbol;		
		std::wstring desc;
	};

	struct sVarInfo
	{			
		std::wstring symbol;		
		std::wstring desc;
	};

	struct sExcepInfo
	{			
		std::wstring id;		
		std::wstring desc;
	};

	struct sLibInfo
	{
		std::wstring title;
		std::wstring desc;
		std::wstring version;
		std::wstring type;
		std::wstring data1, data2;
	};

	std::vector<sFuncInfo> m_funcList;		// list of all functions in the current locale
	std::vector<sOpInfo> m_opList;			// list of all operators in the current locale
	std::vector<sConstInfo> m_constList;	// list of all constants in the current locale
	std::vector<sVarInfo> m_varList;		// list of all variables in the current locale
	std::vector<sExcepInfo> m_excepList;	// list of all exceptions in the current locale
	sLibInfo m_libInfo;
	
};

