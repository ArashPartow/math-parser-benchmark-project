// MTDatePlugin.cpp : Implementation of DLL Exports.

#include "stdafx.h"


#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{12C43572-A2FB-4D74-8C40-D231128B34E4}", 
		 name = "MTDatePlugin", 
		 helpstring = "MTDatePlugin 1.0 Type Library",
		 resource_name = "IDR_MTDATEPLUGIN") ]
class CMTDatePluginModule
{
public:
// Override CAtlDllModuleT members
};
		 
