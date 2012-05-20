

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Mar 09 18:16:39 2008
 */
/* Compiler settings for _MTDatePlugin.idl:
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

#ifndef ___MTDatePlugin_h__
#define ___MTDatePlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMTDatePlugin_FWD_DEFINED__
#define __IMTDatePlugin_FWD_DEFINED__
typedef interface IMTDatePlugin IMTDatePlugin;
#endif 	/* __IMTDatePlugin_FWD_DEFINED__ */


#ifndef __CMTDatePlugin_FWD_DEFINED__
#define __CMTDatePlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMTDatePlugin CMTDatePlugin;
#else
typedef struct CMTDatePlugin CMTDatePlugin;
#endif /* __cplusplus */

#endif 	/* __CMTDatePlugin_FWD_DEFINED__ */


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

#ifndef __IMTDatePlugin_INTERFACE_DEFINED__
#define __IMTDatePlugin_INTERFACE_DEFINED__

/* interface IMTDatePlugin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTDatePlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF39D9F5-EF4F-4356-B035-0A58AD12579F")
    IMTDatePlugin : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMTDatePluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTDatePlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTDatePlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTDatePlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTDatePlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTDatePlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTDatePlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTDatePlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMTDatePluginVtbl;

    interface IMTDatePlugin
    {
        CONST_VTBL struct IMTDatePluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTDatePlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTDatePlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTDatePlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTDatePlugin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTDatePlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTDatePlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTDatePlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMTDatePlugin_INTERFACE_DEFINED__ */



#ifndef __MTDatePlugin_LIBRARY_DEFINED__
#define __MTDatePlugin_LIBRARY_DEFINED__

/* library MTDatePlugin */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_MTDatePlugin;

EXTERN_C const CLSID CLSID_CMTDatePlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("43F6302F-94FD-4702-908D-EA1F157080AD")
CMTDatePlugin;
#endif
#endif /* __MTDatePlugin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


