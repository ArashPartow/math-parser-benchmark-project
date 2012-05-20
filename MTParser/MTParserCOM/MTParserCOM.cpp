// MTParserCOM.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f MTParserCOMps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "MTParserCOM.h"

#include "MTParserCOM_i.c"
#include "MTParser.h"
#include "MTDouble.h"
#include "MTDate.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_MTParser, CMTParser)
OBJECT_ENTRY(CLSID_MTDouble, CMTDouble)
OBJECT_ENTRY(CLSID_MTDate, CMTDate)
END_OBJECT_MAP()

class CMTParserCOMApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMTParserCOMApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMTParserCOMApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

};

BEGIN_MESSAGE_MAP(CMTParserCOMApp, CWinApp)
	//{{AFX_MSG_MAP(CMTParserCOMApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMTParserCOMApp theApp;

BOOL CMTParserCOMApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_MTPARSERCOMLib);


	

    return CWinApp::InitInstance();
}

int CMTParserCOMApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


#include "MTDate.h"
