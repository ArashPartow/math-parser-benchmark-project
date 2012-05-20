

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Mar 09 18:16:54 2008
 */
/* Compiler settings for _MTNumAlgoPlugin.idl:
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

#ifndef ___MTNumAlgoPlugin_h__
#define ___MTNumAlgoPlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMTNumAlgoPlugin_FWD_DEFINED__
#define __IMTNumAlgoPlugin_FWD_DEFINED__
typedef interface IMTNumAlgoPlugin IMTNumAlgoPlugin;
#endif 	/* __IMTNumAlgoPlugin_FWD_DEFINED__ */


#ifndef __CMTNumAlgoPlugin_FWD_DEFINED__
#define __CMTNumAlgoPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMTNumAlgoPlugin CMTNumAlgoPlugin;
#else
typedef struct CMTNumAlgoPlugin CMTNumAlgoPlugin;
#endif /* __cplusplus */

#endif 	/* __CMTNumAlgoPlugin_FWD_DEFINED__ */


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

#ifndef __IMTNumAlgoPlugin_INTERFACE_DEFINED__
#define __IMTNumAlgoPlugin_INTERFACE_DEFINED__

/* interface IMTNumAlgoPlugin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTNumAlgoPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E47FB6D5-A248-48F5-885E-214702CE6A20")
    IMTNumAlgoPlugin : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMTNumAlgoPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTNumAlgoPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTNumAlgoPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTNumAlgoPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTNumAlgoPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTNumAlgoPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTNumAlgoPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTNumAlgoPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMTNumAlgoPluginVtbl;

    interface IMTNumAlgoPlugin
    {
        CONST_VTBL struct IMTNumAlgoPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTNumAlgoPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTNumAlgoPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTNumAlgoPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTNumAlgoPlugin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTNumAlgoPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTNumAlgoPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTNumAlgoPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMTNumAlgoPlugin_INTERFACE_DEFINED__ */



#ifndef __MTNumAlgoPlugin_LIBRARY_DEFINED__
#define __MTNumAlgoPlugin_LIBRARY_DEFINED__

/* library MTNumAlgoPlugin */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_MTNumAlgoPlugin;

EXTERN_C const CLSID CLSID_CMTNumAlgoPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("1F6C2D74-1023-4E0F-8A6B-DBA19E6585E3")
CMTNumAlgoPlugin;
#endif
#endif /* __MTNumAlgoPlugin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


