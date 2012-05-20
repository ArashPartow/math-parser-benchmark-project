

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Mar 09 18:17:30 2008
 */
/* Compiler settings for _MTParserPlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___MTParserPlugin_h__
#define ___MTParserPlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMTParserPlugin_FWD_DEFINED__
#define __IMTParserPlugin_FWD_DEFINED__
typedef interface IMTParserPlugin IMTParserPlugin;
#endif 	/* __IMTParserPlugin_FWD_DEFINED__ */


#ifndef __CMTParserPlugin_FWD_DEFINED__
#define __CMTParserPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMTParserPlugin CMTParserPlugin;
#else
typedef struct CMTParserPlugin CMTParserPlugin;
#endif /* __cplusplus */

#endif 	/* __CMTParserPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMTParserPlugin_INTERFACE_DEFINED__
#define __IMTParserPlugin_INTERFACE_DEFINED__

/* interface IMTParserPlugin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTParserPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("91893C09-F41E-4389-9185-42B2E0D5A49E")
    IMTParserPlugin : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbConsts( 
            /* [retval][out] */ int *pNbConsts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getConst( 
            /* [in] */ int constID,
            /* [retval][out] */ struct SMTPluginConst *pConst) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbFuncs( 
            /* [retval][out] */ int *pNbFuncs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE newFunc( 
            /* [in] */ int funcID,
            /* [retval][out] */ int *pFunc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbOps( 
            /* [retval][out] */ int *pNbOps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE newOp( 
            /* [in] */ int opID,
            /* [retval][out] */ int *pOp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMTParserVersion( 
            /* [retval][out] */ BSTR *pVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getInfoFile( 
            /* [out] */ BSTR *pInfoFile,
            /* [out] */ BSTR *pVersion,
            /* [retval][out] */ int *pIsAvailable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTParserPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTParserPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTParserPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTParserPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTParserPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTParserPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTParserPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTParserPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbConsts )( 
            IMTParserPlugin * This,
            /* [retval][out] */ int *pNbConsts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getConst )( 
            IMTParserPlugin * This,
            /* [in] */ int constID,
            /* [retval][out] */ struct SMTPluginConst *pConst);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbFuncs )( 
            IMTParserPlugin * This,
            /* [retval][out] */ int *pNbFuncs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *newFunc )( 
            IMTParserPlugin * This,
            /* [in] */ int funcID,
            /* [retval][out] */ int *pFunc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbOps )( 
            IMTParserPlugin * This,
            /* [retval][out] */ int *pNbOps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *newOp )( 
            IMTParserPlugin * This,
            /* [in] */ int opID,
            /* [retval][out] */ int *pOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getMTParserVersion )( 
            IMTParserPlugin * This,
            /* [retval][out] */ BSTR *pVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getInfoFile )( 
            IMTParserPlugin * This,
            /* [out] */ BSTR *pInfoFile,
            /* [out] */ BSTR *pVersion,
            /* [retval][out] */ int *pIsAvailable);
        
        END_INTERFACE
    } IMTParserPluginVtbl;

    interface IMTParserPlugin
    {
        CONST_VTBL struct IMTParserPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTParserPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTParserPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTParserPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTParserPlugin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTParserPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTParserPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTParserPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTParserPlugin_getNbConsts(This,pNbConsts)	\
    (This)->lpVtbl -> getNbConsts(This,pNbConsts)

#define IMTParserPlugin_getConst(This,constID,pConst)	\
    (This)->lpVtbl -> getConst(This,constID,pConst)

#define IMTParserPlugin_getNbFuncs(This,pNbFuncs)	\
    (This)->lpVtbl -> getNbFuncs(This,pNbFuncs)

#define IMTParserPlugin_newFunc(This,funcID,pFunc)	\
    (This)->lpVtbl -> newFunc(This,funcID,pFunc)

#define IMTParserPlugin_getNbOps(This,pNbOps)	\
    (This)->lpVtbl -> getNbOps(This,pNbOps)

#define IMTParserPlugin_newOp(This,opID,pOp)	\
    (This)->lpVtbl -> newOp(This,opID,pOp)

#define IMTParserPlugin_getMTParserVersion(This,pVersion)	\
    (This)->lpVtbl -> getMTParserVersion(This,pVersion)

#define IMTParserPlugin_getInfoFile(This,pInfoFile,pVersion,pIsAvailable)	\
    (This)->lpVtbl -> getInfoFile(This,pInfoFile,pVersion,pIsAvailable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getNbConsts_Proxy( 
    IMTParserPlugin * This,
    /* [retval][out] */ int *pNbConsts);


void __RPC_STUB IMTParserPlugin_getNbConsts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getConst_Proxy( 
    IMTParserPlugin * This,
    /* [in] */ int constID,
    /* [retval][out] */ struct SMTPluginConst *pConst);


void __RPC_STUB IMTParserPlugin_getConst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getNbFuncs_Proxy( 
    IMTParserPlugin * This,
    /* [retval][out] */ int *pNbFuncs);


void __RPC_STUB IMTParserPlugin_getNbFuncs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_newFunc_Proxy( 
    IMTParserPlugin * This,
    /* [in] */ int funcID,
    /* [retval][out] */ int *pFunc);


void __RPC_STUB IMTParserPlugin_newFunc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getNbOps_Proxy( 
    IMTParserPlugin * This,
    /* [retval][out] */ int *pNbOps);


void __RPC_STUB IMTParserPlugin_getNbOps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_newOp_Proxy( 
    IMTParserPlugin * This,
    /* [in] */ int opID,
    /* [retval][out] */ int *pOp);


void __RPC_STUB IMTParserPlugin_newOp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getMTParserVersion_Proxy( 
    IMTParserPlugin * This,
    /* [retval][out] */ BSTR *pVersion);


void __RPC_STUB IMTParserPlugin_getMTParserVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserPlugin_getInfoFile_Proxy( 
    IMTParserPlugin * This,
    /* [out] */ BSTR *pInfoFile,
    /* [out] */ BSTR *pVersion,
    /* [retval][out] */ int *pIsAvailable);


void __RPC_STUB IMTParserPlugin_getInfoFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTParserPlugin_INTERFACE_DEFINED__ */



#ifndef __MTParserPlugin_LIBRARY_DEFINED__
#define __MTParserPlugin_LIBRARY_DEFINED__

/* library MTParserPlugin */
/* [helpstring][uuid][version] */ 

/* [uuid][custom] */ struct  DECLSPEC_UUID("9D7C0E14-9312-3884-9F47-BFCFA847AFCF") SMTPluginConst
    {
    BSTR name;
    double val;
    } ;

EXTERN_C const IID LIBID_MTParserPlugin;

EXTERN_C const CLSID CLSID_CMTParserPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("99DA618B-2DA5-444C-AEA2-195C02F11F5A")
CMTParserPlugin;
#endif
#endif /* __MTParserPlugin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


