

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sat Mar 08 15:55:12 2008
 */
/* Compiler settings for .\MTParserCOM.idl:
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

#ifndef __MTParserCOM_h__
#define __MTParserCOM_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMTVariable_FWD_DEFINED__
#define __IMTVariable_FWD_DEFINED__
typedef interface IMTVariable IMTVariable;
#endif 	/* __IMTVariable_FWD_DEFINED__ */


#ifndef __IMTFunction_FWD_DEFINED__
#define __IMTFunction_FWD_DEFINED__
typedef interface IMTFunction IMTFunction;
#endif 	/* __IMTFunction_FWD_DEFINED__ */


#ifndef __IMTParser_FWD_DEFINED__
#define __IMTParser_FWD_DEFINED__
typedef interface IMTParser IMTParser;
#endif 	/* __IMTParser_FWD_DEFINED__ */


#ifndef __IMTDouble_FWD_DEFINED__
#define __IMTDouble_FWD_DEFINED__
typedef interface IMTDouble IMTDouble;
#endif 	/* __IMTDouble_FWD_DEFINED__ */


#ifndef __IMTDate_FWD_DEFINED__
#define __IMTDate_FWD_DEFINED__
typedef interface IMTDate IMTDate;
#endif 	/* __IMTDate_FWD_DEFINED__ */


#ifndef __IMTParserLocalizer_FWD_DEFINED__
#define __IMTParserLocalizer_FWD_DEFINED__
typedef interface IMTParserLocalizer IMTParserLocalizer;
#endif 	/* __IMTParserLocalizer_FWD_DEFINED__ */


#ifndef __IMTExcepData_FWD_DEFINED__
#define __IMTExcepData_FWD_DEFINED__
typedef interface IMTExcepData IMTExcepData;
#endif 	/* __IMTExcepData_FWD_DEFINED__ */


#ifndef __IMTDoubleVector_FWD_DEFINED__
#define __IMTDoubleVector_FWD_DEFINED__
typedef interface IMTDoubleVector IMTDoubleVector;
#endif 	/* __IMTDoubleVector_FWD_DEFINED__ */


#ifndef __MTParser_FWD_DEFINED__
#define __MTParser_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTParser MTParser;
#else
typedef struct MTParser MTParser;
#endif /* __cplusplus */

#endif 	/* __MTParser_FWD_DEFINED__ */


#ifndef __MTDouble_FWD_DEFINED__
#define __MTDouble_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTDouble MTDouble;
#else
typedef struct MTDouble MTDouble;
#endif /* __cplusplus */

#endif 	/* __MTDouble_FWD_DEFINED__ */


#ifndef __MTDate_FWD_DEFINED__
#define __MTDate_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTDate MTDate;
#else
typedef struct MTDate MTDate;
#endif /* __cplusplus */

#endif 	/* __MTDate_FWD_DEFINED__ */


#ifndef __MTParserLocalizer_FWD_DEFINED__
#define __MTParserLocalizer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTParserLocalizer MTParserLocalizer;
#else
typedef struct MTParserLocalizer MTParserLocalizer;
#endif /* __cplusplus */

#endif 	/* __MTParserLocalizer_FWD_DEFINED__ */


#ifndef __MTExcepData_FWD_DEFINED__
#define __MTExcepData_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTExcepData MTExcepData;
#else
typedef struct MTExcepData MTExcepData;
#endif /* __cplusplus */

#endif 	/* __MTExcepData_FWD_DEFINED__ */


#ifndef __MTDoubleVector_FWD_DEFINED__
#define __MTDoubleVector_FWD_DEFINED__

#ifdef __cplusplus
typedef class MTDoubleVector MTDoubleVector;
#else
typedef struct MTDoubleVector MTDoubleVector;
#endif /* __cplusplus */

#endif 	/* __MTDoubleVector_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_MTParserCOM_0000 */
/* [local] */ 

typedef struct sMTConstant
    {
    /* [helpstring] */ BSTR name;
    /* [helpstring] */ double value;
    /* [helpstring] */ BSTR description;
    } 	SMTConstant;

typedef struct sMTFunction
    {
    /* [helpstring] */ BSTR ID;
    /* [helpstring] */ BSTR symbol;
    /* [helpstring] */ BSTR helpString;
    /* [helpstring] */ BSTR description;
    } 	SMTFunction;

typedef struct sMTOperator
    {
    /* [helpstring] */ BSTR ID;
    /* [helpstring] */ BSTR symbol;
    /* [helpstring] */ BSTR helpString;
    /* [helpstring] */ BSTR description;
    } 	SMTOperator;

typedef struct sMTSyntax
    {
    /* [helpstring] */ int decimalPoint;
    /* [helpstring] */ int argumentSeparator;
    } 	SMTSyntax;




extern RPC_IF_HANDLE __MIDL_itf_MTParserCOM_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MTParserCOM_0000_v0_0_s_ifspec;

#ifndef __IMTVariable_INTERFACE_DEFINED__
#define __IMTVariable_INTERFACE_DEFINED__

/* interface IMTVariable */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTVariable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC930F10-590E-5928-BE23-12C694D5B035")
    IMTVariable : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getName( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNativeVar( 
            /* [retval][out] */ int *pVar) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTVariableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTVariable * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTVariable * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTVariable * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTVariable * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTVariable * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTVariable * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTVariable * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getName )( 
            IMTVariable * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNativeVar )( 
            IMTVariable * This,
            /* [retval][out] */ int *pVar);
        
        END_INTERFACE
    } IMTVariableVtbl;

    interface IMTVariable
    {
        CONST_VTBL struct IMTVariableVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTVariable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTVariable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTVariable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTVariable_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTVariable_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTVariable_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTVariable_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTVariable_getName(This,pName)	\
    (This)->lpVtbl -> getName(This,pName)

#define IMTVariable_getNativeVar(This,pVar)	\
    (This)->lpVtbl -> getNativeVar(This,pVar)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTVariable_getName_Proxy( 
    IMTVariable * This,
    /* [retval][out] */ BSTR *pName);


void __RPC_STUB IMTVariable_getName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTVariable_getNativeVar_Proxy( 
    IMTVariable * This,
    /* [retval][out] */ int *pVar);


void __RPC_STUB IMTVariable_getNativeVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTVariable_INTERFACE_DEFINED__ */


#ifndef __IMTFunction_INTERFACE_DEFINED__
#define __IMTFunction_INTERFACE_DEFINED__

/* interface IMTFunction */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED930F11-520E-5926-BE23-12C694D5B035")
    IMTFunction : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSymbol( 
            /* [retval][out] */ BSTR *pSymbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getHelpString( 
            /* [retval][out] */ BSTR *pHelpString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getDescription( 
            /* [retval][out] */ BSTR *pDescription) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbArgs( 
            /* [retval][out] */ int *pNbArgs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate0( 
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate1( 
            /* [in] */ double arg,
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate2( 
            /* [in] */ double arg,
            /* [in] */ double arg2,
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate3( 
            /* [in] */ double arg,
            /* [in] */ double arg2,
            /* [in] */ double arg3,
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate( 
            /* [in] */ SAFEARRAY * pArgs,
            /* [retval][out] */ double *pResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTFunction * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTFunction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTFunction * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTFunction * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTFunction * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTFunction * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTFunction * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getSymbol )( 
            IMTFunction * This,
            /* [retval][out] */ BSTR *pSymbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getHelpString )( 
            IMTFunction * This,
            /* [retval][out] */ BSTR *pHelpString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getDescription )( 
            IMTFunction * This,
            /* [retval][out] */ BSTR *pDescription);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbArgs )( 
            IMTFunction * This,
            /* [retval][out] */ int *pNbArgs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate0 )( 
            IMTFunction * This,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate1 )( 
            IMTFunction * This,
            /* [in] */ double arg,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate2 )( 
            IMTFunction * This,
            /* [in] */ double arg,
            /* [in] */ double arg2,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate3 )( 
            IMTFunction * This,
            /* [in] */ double arg,
            /* [in] */ double arg2,
            /* [in] */ double arg3,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate )( 
            IMTFunction * This,
            /* [in] */ SAFEARRAY * pArgs,
            /* [retval][out] */ double *pResult);
        
        END_INTERFACE
    } IMTFunctionVtbl;

    interface IMTFunction
    {
        CONST_VTBL struct IMTFunctionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTFunction_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTFunction_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTFunction_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTFunction_getSymbol(This,pSymbol)	\
    (This)->lpVtbl -> getSymbol(This,pSymbol)

#define IMTFunction_getHelpString(This,pHelpString)	\
    (This)->lpVtbl -> getHelpString(This,pHelpString)

#define IMTFunction_getDescription(This,pDescription)	\
    (This)->lpVtbl -> getDescription(This,pDescription)

#define IMTFunction_getNbArgs(This,pNbArgs)	\
    (This)->lpVtbl -> getNbArgs(This,pNbArgs)

#define IMTFunction_evaluate0(This,pResult)	\
    (This)->lpVtbl -> evaluate0(This,pResult)

#define IMTFunction_evaluate1(This,arg,pResult)	\
    (This)->lpVtbl -> evaluate1(This,arg,pResult)

#define IMTFunction_evaluate2(This,arg,arg2,pResult)	\
    (This)->lpVtbl -> evaluate2(This,arg,arg2,pResult)

#define IMTFunction_evaluate3(This,arg,arg2,arg3,pResult)	\
    (This)->lpVtbl -> evaluate3(This,arg,arg2,arg3,pResult)

#define IMTFunction_evaluate(This,pArgs,pResult)	\
    (This)->lpVtbl -> evaluate(This,pArgs,pResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_getSymbol_Proxy( 
    IMTFunction * This,
    /* [retval][out] */ BSTR *pSymbol);


void __RPC_STUB IMTFunction_getSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_getHelpString_Proxy( 
    IMTFunction * This,
    /* [retval][out] */ BSTR *pHelpString);


void __RPC_STUB IMTFunction_getHelpString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_getDescription_Proxy( 
    IMTFunction * This,
    /* [retval][out] */ BSTR *pDescription);


void __RPC_STUB IMTFunction_getDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_getNbArgs_Proxy( 
    IMTFunction * This,
    /* [retval][out] */ int *pNbArgs);


void __RPC_STUB IMTFunction_getNbArgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_evaluate0_Proxy( 
    IMTFunction * This,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTFunction_evaluate0_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_evaluate1_Proxy( 
    IMTFunction * This,
    /* [in] */ double arg,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTFunction_evaluate1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_evaluate2_Proxy( 
    IMTFunction * This,
    /* [in] */ double arg,
    /* [in] */ double arg2,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTFunction_evaluate2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_evaluate3_Proxy( 
    IMTFunction * This,
    /* [in] */ double arg,
    /* [in] */ double arg2,
    /* [in] */ double arg3,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTFunction_evaluate3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTFunction_evaluate_Proxy( 
    IMTFunction * This,
    /* [in] */ SAFEARRAY * pArgs,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTFunction_evaluate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTFunction_INTERFACE_DEFINED__ */


#ifndef __IMTParser_INTERFACE_DEFINED__
#define __IMTParser_INTERFACE_DEFINED__

/* interface IMTParser */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTParser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AB830D10-490E-4228-AE23-01C794E5C036")
    IMTParser : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluateCompiled( 
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE compile( 
            /* [in] */ BSTR expr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluate( 
            /* [in] */ BSTR expr,
            /* [retval][out] */ double *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineVar( 
            /* [in] */ BSTR symbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineAllVars( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE resetExpression( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadPlugin( 
            /* [in] */ BSTR clsid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE useLocaleSettings( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setSyntax( 
            /* [in] */ SMTSyntax *pSyntax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSyntax( 
            /* [retval][out] */ SMTSyntax *pSyntax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE defineConst( 
            /* [in] */ BSTR name,
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getParserPtr( 
            /* [out] */ int *pParserPtr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE copy( 
            /* [in] */ IMTParser *pParser) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbUsedVars( 
            /* [retval][out] */ int *pNbUsedVars) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getUsedVar( 
            /* [in] */ int index,
            /* [retval][out] */ BSTR *symbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbDefinedConsts( 
            /* [retval][out] */ int *pNbDefinedConsts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getConst( 
            /* [in] */ int index,
            /* [retval][out] */ SMTConstant *pConst) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbDefinedFuncs( 
            /* [retval][out] */ int *pNbDefinedFuncs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getFunc( 
            /* [in] */ int index,
            /* [retval][out] */ SMTFunction *pFunc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbDefinedOps( 
            /* [retval][out] */ int *pNbDefinedOps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOp( 
            /* [in] */ int index,
            /* [retval][out] */ SMTOperator *pOp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLastExcep( 
            /* [in] */ IMTExcepData *pExcep) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE defineVar( 
            /* [in] */ IMTVariable *pVar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNaN( 
            /* [retval][out] */ double *pNaN) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isNaN( 
            /* [retval][out] */ int *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE defineMacro( 
            /* [in] */ BSTR prototype,
            /* [in] */ BSTR macro,
            /* [in] */ BSTR description) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isFinite( 
            /* [retval][out] */ int *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadAllPlugins( 
            /* [in] */ BSTR directory,
            /* [in] */ BSTR searchPattern) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluateCompiledBatch( 
            /* [in] */ int nbLoops,
            /* [out][in] */ SAFEARRAY * pResults) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE redefineVar( 
            /* [in] */ IMTVariable *pVar) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_expression( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_expression( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_autoVarDefinitionEnabled( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_autoVarDefinitionEnabled( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_syntax( 
            /* [retval][out] */ SMTSyntax *pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_syntax( 
            /* [in] */ SMTSyntax newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineConst( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineFuncById( 
            /* [in] */ BSTR id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineOpById( 
            /* [in] */ BSTR id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineFuncsBySymbol( 
            /* [in] */ BSTR symbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE undefineOpsBySymbol( 
            /* [in] */ BSTR symbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbDefinedVars( 
            /* [retval][out] */ int *pNbDefinedOps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVar( 
            /* [in] */ int index,
            /* [retval][out] */ BSTR *symbol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE defineFunc( 
            /* [in] */ IMTFunction *pFunc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE evaluateCompiledBatchVB6( 
            /* [in] */ int nbLoops,
            /* [out][in] */ SAFEARRAY * *pResults) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTParserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTParser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTParser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTParser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTParser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTParser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTParser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTParser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluateCompiled )( 
            IMTParser * This,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *compile )( 
            IMTParser * This,
            /* [in] */ BSTR expr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluate )( 
            IMTParser * This,
            /* [in] */ BSTR expr,
            /* [retval][out] */ double *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineVar )( 
            IMTParser * This,
            /* [in] */ BSTR symbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineAllVars )( 
            IMTParser * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *resetExpression )( 
            IMTParser * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *loadPlugin )( 
            IMTParser * This,
            /* [in] */ BSTR clsid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *useLocaleSettings )( 
            IMTParser * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setSyntax )( 
            IMTParser * This,
            /* [in] */ SMTSyntax *pSyntax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getSyntax )( 
            IMTParser * This,
            /* [retval][out] */ SMTSyntax *pSyntax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *defineConst )( 
            IMTParser * This,
            /* [in] */ BSTR name,
            /* [in] */ double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getParserPtr )( 
            IMTParser * This,
            /* [out] */ int *pParserPtr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *copy )( 
            IMTParser * This,
            /* [in] */ IMTParser *pParser);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbUsedVars )( 
            IMTParser * This,
            /* [retval][out] */ int *pNbUsedVars);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getUsedVar )( 
            IMTParser * This,
            /* [in] */ int index,
            /* [retval][out] */ BSTR *symbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbDefinedConsts )( 
            IMTParser * This,
            /* [retval][out] */ int *pNbDefinedConsts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getConst )( 
            IMTParser * This,
            /* [in] */ int index,
            /* [retval][out] */ SMTConstant *pConst);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbDefinedFuncs )( 
            IMTParser * This,
            /* [retval][out] */ int *pNbDefinedFuncs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getFunc )( 
            IMTParser * This,
            /* [in] */ int index,
            /* [retval][out] */ SMTFunction *pFunc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbDefinedOps )( 
            IMTParser * This,
            /* [retval][out] */ int *pNbDefinedOps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getOp )( 
            IMTParser * This,
            /* [in] */ int index,
            /* [retval][out] */ SMTOperator *pOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLastExcep )( 
            IMTParser * This,
            /* [in] */ IMTExcepData *pExcep);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *defineVar )( 
            IMTParser * This,
            /* [in] */ IMTVariable *pVar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNaN )( 
            IMTParser * This,
            /* [retval][out] */ double *pNaN);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isNaN )( 
            IMTParser * This,
            /* [retval][out] */ int *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *defineMacro )( 
            IMTParser * This,
            /* [in] */ BSTR prototype,
            /* [in] */ BSTR macro,
            /* [in] */ BSTR description);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isFinite )( 
            IMTParser * This,
            /* [retval][out] */ int *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *loadAllPlugins )( 
            IMTParser * This,
            /* [in] */ BSTR directory,
            /* [in] */ BSTR searchPattern);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluateCompiledBatch )( 
            IMTParser * This,
            /* [in] */ int nbLoops,
            /* [out][in] */ SAFEARRAY * pResults);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *redefineVar )( 
            IMTParser * This,
            /* [in] */ IMTVariable *pVar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_expression )( 
            IMTParser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_expression )( 
            IMTParser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_autoVarDefinitionEnabled )( 
            IMTParser * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_autoVarDefinitionEnabled )( 
            IMTParser * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_syntax )( 
            IMTParser * This,
            /* [retval][out] */ SMTSyntax *pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_syntax )( 
            IMTParser * This,
            /* [in] */ SMTSyntax newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineConst )( 
            IMTParser * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineFuncById )( 
            IMTParser * This,
            /* [in] */ BSTR id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineOpById )( 
            IMTParser * This,
            /* [in] */ BSTR id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineFuncsBySymbol )( 
            IMTParser * This,
            /* [in] */ BSTR symbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *undefineOpsBySymbol )( 
            IMTParser * This,
            /* [in] */ BSTR symbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbDefinedVars )( 
            IMTParser * This,
            /* [retval][out] */ int *pNbDefinedOps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getVar )( 
            IMTParser * This,
            /* [in] */ int index,
            /* [retval][out] */ BSTR *symbol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *defineFunc )( 
            IMTParser * This,
            /* [in] */ IMTFunction *pFunc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *evaluateCompiledBatchVB6 )( 
            IMTParser * This,
            /* [in] */ int nbLoops,
            /* [out][in] */ SAFEARRAY * *pResults);
        
        END_INTERFACE
    } IMTParserVtbl;

    interface IMTParser
    {
        CONST_VTBL struct IMTParserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTParser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTParser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTParser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTParser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTParser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTParser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTParser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTParser_evaluateCompiled(This,pResult)	\
    (This)->lpVtbl -> evaluateCompiled(This,pResult)

#define IMTParser_compile(This,expr)	\
    (This)->lpVtbl -> compile(This,expr)

#define IMTParser_evaluate(This,expr,pResult)	\
    (This)->lpVtbl -> evaluate(This,expr,pResult)

#define IMTParser_undefineVar(This,symbol)	\
    (This)->lpVtbl -> undefineVar(This,symbol)

#define IMTParser_undefineAllVars(This)	\
    (This)->lpVtbl -> undefineAllVars(This)

#define IMTParser_resetExpression(This)	\
    (This)->lpVtbl -> resetExpression(This)

#define IMTParser_loadPlugin(This,clsid)	\
    (This)->lpVtbl -> loadPlugin(This,clsid)

#define IMTParser_useLocaleSettings(This)	\
    (This)->lpVtbl -> useLocaleSettings(This)

#define IMTParser_setSyntax(This,pSyntax)	\
    (This)->lpVtbl -> setSyntax(This,pSyntax)

#define IMTParser_getSyntax(This,pSyntax)	\
    (This)->lpVtbl -> getSyntax(This,pSyntax)

#define IMTParser_defineConst(This,name,value)	\
    (This)->lpVtbl -> defineConst(This,name,value)

#define IMTParser_getParserPtr(This,pParserPtr)	\
    (This)->lpVtbl -> getParserPtr(This,pParserPtr)

#define IMTParser_copy(This,pParser)	\
    (This)->lpVtbl -> copy(This,pParser)

#define IMTParser_getNbUsedVars(This,pNbUsedVars)	\
    (This)->lpVtbl -> getNbUsedVars(This,pNbUsedVars)

#define IMTParser_getUsedVar(This,index,symbol)	\
    (This)->lpVtbl -> getUsedVar(This,index,symbol)

#define IMTParser_getNbDefinedConsts(This,pNbDefinedConsts)	\
    (This)->lpVtbl -> getNbDefinedConsts(This,pNbDefinedConsts)

#define IMTParser_getConst(This,index,pConst)	\
    (This)->lpVtbl -> getConst(This,index,pConst)

#define IMTParser_getNbDefinedFuncs(This,pNbDefinedFuncs)	\
    (This)->lpVtbl -> getNbDefinedFuncs(This,pNbDefinedFuncs)

#define IMTParser_getFunc(This,index,pFunc)	\
    (This)->lpVtbl -> getFunc(This,index,pFunc)

#define IMTParser_getNbDefinedOps(This,pNbDefinedOps)	\
    (This)->lpVtbl -> getNbDefinedOps(This,pNbDefinedOps)

#define IMTParser_getOp(This,index,pOp)	\
    (This)->lpVtbl -> getOp(This,index,pOp)

#define IMTParser_getLastExcep(This,pExcep)	\
    (This)->lpVtbl -> getLastExcep(This,pExcep)

#define IMTParser_defineVar(This,pVar)	\
    (This)->lpVtbl -> defineVar(This,pVar)

#define IMTParser_getNaN(This,pNaN)	\
    (This)->lpVtbl -> getNaN(This,pNaN)

#define IMTParser_isNaN(This,pRet)	\
    (This)->lpVtbl -> isNaN(This,pRet)

#define IMTParser_defineMacro(This,prototype,macro,description)	\
    (This)->lpVtbl -> defineMacro(This,prototype,macro,description)

#define IMTParser_isFinite(This,pRet)	\
    (This)->lpVtbl -> isFinite(This,pRet)

#define IMTParser_loadAllPlugins(This,directory,searchPattern)	\
    (This)->lpVtbl -> loadAllPlugins(This,directory,searchPattern)

#define IMTParser_evaluateCompiledBatch(This,nbLoops,pResults)	\
    (This)->lpVtbl -> evaluateCompiledBatch(This,nbLoops,pResults)

#define IMTParser_redefineVar(This,pVar)	\
    (This)->lpVtbl -> redefineVar(This,pVar)

#define IMTParser_get_expression(This,pVal)	\
    (This)->lpVtbl -> get_expression(This,pVal)

#define IMTParser_put_expression(This,newVal)	\
    (This)->lpVtbl -> put_expression(This,newVal)

#define IMTParser_get_autoVarDefinitionEnabled(This,pVal)	\
    (This)->lpVtbl -> get_autoVarDefinitionEnabled(This,pVal)

#define IMTParser_put_autoVarDefinitionEnabled(This,newVal)	\
    (This)->lpVtbl -> put_autoVarDefinitionEnabled(This,newVal)

#define IMTParser_get_syntax(This,pVal)	\
    (This)->lpVtbl -> get_syntax(This,pVal)

#define IMTParser_putref_syntax(This,newVal)	\
    (This)->lpVtbl -> putref_syntax(This,newVal)

#define IMTParser_undefineConst(This,name)	\
    (This)->lpVtbl -> undefineConst(This,name)

#define IMTParser_undefineFuncById(This,id)	\
    (This)->lpVtbl -> undefineFuncById(This,id)

#define IMTParser_undefineOpById(This,id)	\
    (This)->lpVtbl -> undefineOpById(This,id)

#define IMTParser_undefineFuncsBySymbol(This,symbol)	\
    (This)->lpVtbl -> undefineFuncsBySymbol(This,symbol)

#define IMTParser_undefineOpsBySymbol(This,symbol)	\
    (This)->lpVtbl -> undefineOpsBySymbol(This,symbol)

#define IMTParser_getNbDefinedVars(This,pNbDefinedOps)	\
    (This)->lpVtbl -> getNbDefinedVars(This,pNbDefinedOps)

#define IMTParser_getVar(This,index,symbol)	\
    (This)->lpVtbl -> getVar(This,index,symbol)

#define IMTParser_defineFunc(This,pFunc)	\
    (This)->lpVtbl -> defineFunc(This,pFunc)

#define IMTParser_evaluateCompiledBatchVB6(This,nbLoops,pResults)	\
    (This)->lpVtbl -> evaluateCompiledBatchVB6(This,nbLoops,pResults)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_evaluateCompiled_Proxy( 
    IMTParser * This,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTParser_evaluateCompiled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_compile_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR expr);


void __RPC_STUB IMTParser_compile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_evaluate_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR expr,
    /* [retval][out] */ double *pResult);


void __RPC_STUB IMTParser_evaluate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineVar_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR symbol);


void __RPC_STUB IMTParser_undefineVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineAllVars_Proxy( 
    IMTParser * This);


void __RPC_STUB IMTParser_undefineAllVars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_resetExpression_Proxy( 
    IMTParser * This);


void __RPC_STUB IMTParser_resetExpression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_loadPlugin_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR clsid);


void __RPC_STUB IMTParser_loadPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_useLocaleSettings_Proxy( 
    IMTParser * This);


void __RPC_STUB IMTParser_useLocaleSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_setSyntax_Proxy( 
    IMTParser * This,
    /* [in] */ SMTSyntax *pSyntax);


void __RPC_STUB IMTParser_setSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getSyntax_Proxy( 
    IMTParser * This,
    /* [retval][out] */ SMTSyntax *pSyntax);


void __RPC_STUB IMTParser_getSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_defineConst_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR name,
    /* [in] */ double value);


void __RPC_STUB IMTParser_defineConst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getParserPtr_Proxy( 
    IMTParser * This,
    /* [out] */ int *pParserPtr);


void __RPC_STUB IMTParser_getParserPtr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_copy_Proxy( 
    IMTParser * This,
    /* [in] */ IMTParser *pParser);


void __RPC_STUB IMTParser_copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNbUsedVars_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pNbUsedVars);


void __RPC_STUB IMTParser_getNbUsedVars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getUsedVar_Proxy( 
    IMTParser * This,
    /* [in] */ int index,
    /* [retval][out] */ BSTR *symbol);


void __RPC_STUB IMTParser_getUsedVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNbDefinedConsts_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pNbDefinedConsts);


void __RPC_STUB IMTParser_getNbDefinedConsts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getConst_Proxy( 
    IMTParser * This,
    /* [in] */ int index,
    /* [retval][out] */ SMTConstant *pConst);


void __RPC_STUB IMTParser_getConst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNbDefinedFuncs_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pNbDefinedFuncs);


void __RPC_STUB IMTParser_getNbDefinedFuncs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getFunc_Proxy( 
    IMTParser * This,
    /* [in] */ int index,
    /* [retval][out] */ SMTFunction *pFunc);


void __RPC_STUB IMTParser_getFunc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNbDefinedOps_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pNbDefinedOps);


void __RPC_STUB IMTParser_getNbDefinedOps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getOp_Proxy( 
    IMTParser * This,
    /* [in] */ int index,
    /* [retval][out] */ SMTOperator *pOp);


void __RPC_STUB IMTParser_getOp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getLastExcep_Proxy( 
    IMTParser * This,
    /* [in] */ IMTExcepData *pExcep);


void __RPC_STUB IMTParser_getLastExcep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_defineVar_Proxy( 
    IMTParser * This,
    /* [in] */ IMTVariable *pVar);


void __RPC_STUB IMTParser_defineVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNaN_Proxy( 
    IMTParser * This,
    /* [retval][out] */ double *pNaN);


void __RPC_STUB IMTParser_getNaN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_isNaN_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pRet);


void __RPC_STUB IMTParser_isNaN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_defineMacro_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR prototype,
    /* [in] */ BSTR macro,
    /* [in] */ BSTR description);


void __RPC_STUB IMTParser_defineMacro_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_isFinite_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pRet);


void __RPC_STUB IMTParser_isFinite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_loadAllPlugins_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR directory,
    /* [in] */ BSTR searchPattern);


void __RPC_STUB IMTParser_loadAllPlugins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_evaluateCompiledBatch_Proxy( 
    IMTParser * This,
    /* [in] */ int nbLoops,
    /* [out][in] */ SAFEARRAY * pResults);


void __RPC_STUB IMTParser_evaluateCompiledBatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_redefineVar_Proxy( 
    IMTParser * This,
    /* [in] */ IMTVariable *pVar);


void __RPC_STUB IMTParser_redefineVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTParser_get_expression_Proxy( 
    IMTParser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMTParser_get_expression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMTParser_put_expression_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMTParser_put_expression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTParser_get_autoVarDefinitionEnabled_Proxy( 
    IMTParser * This,
    /* [retval][out] */ SHORT *pVal);


void __RPC_STUB IMTParser_get_autoVarDefinitionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMTParser_put_autoVarDefinitionEnabled_Proxy( 
    IMTParser * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB IMTParser_put_autoVarDefinitionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTParser_get_syntax_Proxy( 
    IMTParser * This,
    /* [retval][out] */ SMTSyntax *pVal);


void __RPC_STUB IMTParser_get_syntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IMTParser_putref_syntax_Proxy( 
    IMTParser * This,
    /* [in] */ SMTSyntax newVal);


void __RPC_STUB IMTParser_putref_syntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineConst_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR name);


void __RPC_STUB IMTParser_undefineConst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineFuncById_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR id);


void __RPC_STUB IMTParser_undefineFuncById_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineOpById_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR id);


void __RPC_STUB IMTParser_undefineOpById_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineFuncsBySymbol_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR symbol);


void __RPC_STUB IMTParser_undefineFuncsBySymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_undefineOpsBySymbol_Proxy( 
    IMTParser * This,
    /* [in] */ BSTR symbol);


void __RPC_STUB IMTParser_undefineOpsBySymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getNbDefinedVars_Proxy( 
    IMTParser * This,
    /* [retval][out] */ int *pNbDefinedOps);


void __RPC_STUB IMTParser_getNbDefinedVars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_getVar_Proxy( 
    IMTParser * This,
    /* [in] */ int index,
    /* [retval][out] */ BSTR *symbol);


void __RPC_STUB IMTParser_getVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_defineFunc_Proxy( 
    IMTParser * This,
    /* [in] */ IMTFunction *pFunc);


void __RPC_STUB IMTParser_defineFunc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParser_evaluateCompiledBatchVB6_Proxy( 
    IMTParser * This,
    /* [in] */ int nbLoops,
    /* [out][in] */ SAFEARRAY * *pResults);


void __RPC_STUB IMTParser_evaluateCompiledBatchVB6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTParser_INTERFACE_DEFINED__ */


#ifndef __IMTDouble_INTERFACE_DEFINED__
#define __IMTDouble_INTERFACE_DEFINED__

/* interface IMTDouble */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTDouble;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("287D18CE-1D30-4909-80D2-DF45DA3010F4")
    IMTDouble : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE create( 
            /* [in] */ BSTR name,
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValue( 
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getValue( 
            /* [retval][out] */ double *pValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTDoubleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTDouble * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTDouble * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTDouble * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTDouble * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTDouble * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTDouble * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTDouble * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *create )( 
            IMTDouble * This,
            /* [in] */ BSTR name,
            /* [in] */ double value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_value )( 
            IMTDouble * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_value )( 
            IMTDouble * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IMTDouble * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setValue )( 
            IMTDouble * This,
            /* [in] */ double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getValue )( 
            IMTDouble * This,
            /* [retval][out] */ double *pValue);
        
        END_INTERFACE
    } IMTDoubleVtbl;

    interface IMTDouble
    {
        CONST_VTBL struct IMTDoubleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTDouble_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTDouble_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTDouble_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTDouble_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTDouble_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTDouble_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTDouble_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTDouble_create(This,name,value)	\
    (This)->lpVtbl -> create(This,name,value)

#define IMTDouble_get_value(This,pVal)	\
    (This)->lpVtbl -> get_value(This,pVal)

#define IMTDouble_put_value(This,newVal)	\
    (This)->lpVtbl -> put_value(This,newVal)

#define IMTDouble_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IMTDouble_setValue(This,value)	\
    (This)->lpVtbl -> setValue(This,value)

#define IMTDouble_getValue(This,pValue)	\
    (This)->lpVtbl -> getValue(This,pValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDouble_create_Proxy( 
    IMTDouble * This,
    /* [in] */ BSTR name,
    /* [in] */ double value);


void __RPC_STUB IMTDouble_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTDouble_get_value_Proxy( 
    IMTDouble * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IMTDouble_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMTDouble_put_value_Proxy( 
    IMTDouble * This,
    /* [in] */ double newVal);


void __RPC_STUB IMTDouble_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTDouble_get_name_Proxy( 
    IMTDouble * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMTDouble_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDouble_setValue_Proxy( 
    IMTDouble * This,
    /* [in] */ double value);


void __RPC_STUB IMTDouble_setValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDouble_getValue_Proxy( 
    IMTDouble * This,
    /* [retval][out] */ double *pValue);


void __RPC_STUB IMTDouble_getValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTDouble_INTERFACE_DEFINED__ */


#ifndef __IMTDate_INTERFACE_DEFINED__
#define __IMTDate_INTERFACE_DEFINED__

/* interface IMTDate */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTDate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3761F15D-E3AC-43D5-AA4A-333B4F7136D9")
    IMTDate : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE create( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE parseDateTime( 
            /* [in] */ BSTR datetime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setDate( 
            /* [in] */ int year,
            /* [in] */ int month,
            /* [in] */ int day) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setTime( 
            /* [in] */ int hour,
            /* [in] */ int minute,
            /* [in] */ int second) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE format( 
            /* [retval][out] */ BSTR *pDateStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValue( 
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getValue( 
            /* [retval][out] */ double *pValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTDateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTDate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTDate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTDate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTDate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTDate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTDate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTDate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *create )( 
            IMTDate * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *parseDateTime )( 
            IMTDate * This,
            /* [in] */ BSTR datetime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setDate )( 
            IMTDate * This,
            /* [in] */ int year,
            /* [in] */ int month,
            /* [in] */ int day);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTime )( 
            IMTDate * This,
            /* [in] */ int hour,
            /* [in] */ int minute,
            /* [in] */ int second);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IMTDate * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_value )( 
            IMTDate * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_value )( 
            IMTDate * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *format )( 
            IMTDate * This,
            /* [retval][out] */ BSTR *pDateStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setValue )( 
            IMTDate * This,
            /* [in] */ double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getValue )( 
            IMTDate * This,
            /* [retval][out] */ double *pValue);
        
        END_INTERFACE
    } IMTDateVtbl;

    interface IMTDate
    {
        CONST_VTBL struct IMTDateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTDate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTDate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTDate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTDate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTDate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTDate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTDate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTDate_create(This,name)	\
    (This)->lpVtbl -> create(This,name)

#define IMTDate_parseDateTime(This,datetime)	\
    (This)->lpVtbl -> parseDateTime(This,datetime)

#define IMTDate_setDate(This,year,month,day)	\
    (This)->lpVtbl -> setDate(This,year,month,day)

#define IMTDate_setTime(This,hour,minute,second)	\
    (This)->lpVtbl -> setTime(This,hour,minute,second)

#define IMTDate_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IMTDate_get_value(This,pVal)	\
    (This)->lpVtbl -> get_value(This,pVal)

#define IMTDate_put_value(This,newVal)	\
    (This)->lpVtbl -> put_value(This,newVal)

#define IMTDate_format(This,pDateStr)	\
    (This)->lpVtbl -> format(This,pDateStr)

#define IMTDate_setValue(This,value)	\
    (This)->lpVtbl -> setValue(This,value)

#define IMTDate_getValue(This,pValue)	\
    (This)->lpVtbl -> getValue(This,pValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_create_Proxy( 
    IMTDate * This,
    /* [in] */ BSTR name);


void __RPC_STUB IMTDate_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_parseDateTime_Proxy( 
    IMTDate * This,
    /* [in] */ BSTR datetime);


void __RPC_STUB IMTDate_parseDateTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_setDate_Proxy( 
    IMTDate * This,
    /* [in] */ int year,
    /* [in] */ int month,
    /* [in] */ int day);


void __RPC_STUB IMTDate_setDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_setTime_Proxy( 
    IMTDate * This,
    /* [in] */ int hour,
    /* [in] */ int minute,
    /* [in] */ int second);


void __RPC_STUB IMTDate_setTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTDate_get_name_Proxy( 
    IMTDate * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMTDate_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTDate_get_value_Proxy( 
    IMTDate * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IMTDate_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMTDate_put_value_Proxy( 
    IMTDate * This,
    /* [in] */ double newVal);


void __RPC_STUB IMTDate_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_format_Proxy( 
    IMTDate * This,
    /* [retval][out] */ BSTR *pDateStr);


void __RPC_STUB IMTDate_format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_setValue_Proxy( 
    IMTDate * This,
    /* [in] */ double value);


void __RPC_STUB IMTDate_setValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDate_getValue_Proxy( 
    IMTDate * This,
    /* [retval][out] */ double *pValue);


void __RPC_STUB IMTDate_getValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTDate_INTERFACE_DEFINED__ */


#ifndef __IMTParserLocalizer_INTERFACE_DEFINED__
#define __IMTParserLocalizer_INTERFACE_DEFINED__

/* interface IMTParserLocalizer */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTParserLocalizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("138338B4-B343-43C6-B4BB-2A6172875E47")
    IMTParserLocalizer : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE registerLibrary( 
            /* [in] */ BSTR infoFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setLocale( 
            /* [in] */ BSTR locale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbFuncs( 
            /* [retval][out] */ int *pNbFuncs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbOps( 
            /* [retval][out] */ int *pNbOps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbConsts( 
            /* [retval][out] */ int *pNbConsts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getFuncInfo( 
            /* [in] */ BSTR ID,
            /* [in] */ SMTSyntax *pSyntax,
            /* [retval][out] */ SMTFunction *pInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOpInfo( 
            /* [in] */ BSTR ID,
            /* [retval][out] */ SMTOperator *pInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getConstInfo( 
            /* [in] */ BSTR symbol,
            /* [retval][out] */ SMTConstant *pInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE formatExcep( 
            /* [in] */ IMTExcepData *pE,
            /* [in] */ BSTR *msg,
            /* [retval][out] */ BSTR *formattedMsg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE registerAllLibraries( 
            /* [in] */ BSTR directory,
            /* [in] */ BSTR searchPattern) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getExcep( 
            /* [in] */ IMTExcepData *pExcepData,
            /* [retval][out] */ BSTR *pMsg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLastExcep( 
            /* [in] */ IMTExcepData *pExcep) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_locale( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_locale( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTParserLocalizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTParserLocalizer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTParserLocalizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTParserLocalizer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTParserLocalizer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTParserLocalizer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTParserLocalizer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTParserLocalizer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *registerLibrary )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR infoFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setLocale )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR locale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbFuncs )( 
            IMTParserLocalizer * This,
            /* [retval][out] */ int *pNbFuncs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbOps )( 
            IMTParserLocalizer * This,
            /* [retval][out] */ int *pNbOps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbConsts )( 
            IMTParserLocalizer * This,
            /* [retval][out] */ int *pNbConsts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getFuncInfo )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR ID,
            /* [in] */ SMTSyntax *pSyntax,
            /* [retval][out] */ SMTFunction *pInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getOpInfo )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR ID,
            /* [retval][out] */ SMTOperator *pInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getConstInfo )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR symbol,
            /* [retval][out] */ SMTConstant *pInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *formatExcep )( 
            IMTParserLocalizer * This,
            /* [in] */ IMTExcepData *pE,
            /* [in] */ BSTR *msg,
            /* [retval][out] */ BSTR *formattedMsg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *registerAllLibraries )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR directory,
            /* [in] */ BSTR searchPattern);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getExcep )( 
            IMTParserLocalizer * This,
            /* [in] */ IMTExcepData *pExcepData,
            /* [retval][out] */ BSTR *pMsg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLastExcep )( 
            IMTParserLocalizer * This,
            /* [in] */ IMTExcepData *pExcep);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_locale )( 
            IMTParserLocalizer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_locale )( 
            IMTParserLocalizer * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IMTParserLocalizerVtbl;

    interface IMTParserLocalizer
    {
        CONST_VTBL struct IMTParserLocalizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTParserLocalizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTParserLocalizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTParserLocalizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTParserLocalizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTParserLocalizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTParserLocalizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTParserLocalizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTParserLocalizer_registerLibrary(This,infoFile)	\
    (This)->lpVtbl -> registerLibrary(This,infoFile)

#define IMTParserLocalizer_setLocale(This,locale)	\
    (This)->lpVtbl -> setLocale(This,locale)

#define IMTParserLocalizer_getNbFuncs(This,pNbFuncs)	\
    (This)->lpVtbl -> getNbFuncs(This,pNbFuncs)

#define IMTParserLocalizer_getNbOps(This,pNbOps)	\
    (This)->lpVtbl -> getNbOps(This,pNbOps)

#define IMTParserLocalizer_getNbConsts(This,pNbConsts)	\
    (This)->lpVtbl -> getNbConsts(This,pNbConsts)

#define IMTParserLocalizer_getFuncInfo(This,ID,pSyntax,pInfo)	\
    (This)->lpVtbl -> getFuncInfo(This,ID,pSyntax,pInfo)

#define IMTParserLocalizer_getOpInfo(This,ID,pInfo)	\
    (This)->lpVtbl -> getOpInfo(This,ID,pInfo)

#define IMTParserLocalizer_getConstInfo(This,symbol,pInfo)	\
    (This)->lpVtbl -> getConstInfo(This,symbol,pInfo)

#define IMTParserLocalizer_formatExcep(This,pE,msg,formattedMsg)	\
    (This)->lpVtbl -> formatExcep(This,pE,msg,formattedMsg)

#define IMTParserLocalizer_registerAllLibraries(This,directory,searchPattern)	\
    (This)->lpVtbl -> registerAllLibraries(This,directory,searchPattern)

#define IMTParserLocalizer_getExcep(This,pExcepData,pMsg)	\
    (This)->lpVtbl -> getExcep(This,pExcepData,pMsg)

#define IMTParserLocalizer_getLastExcep(This,pExcep)	\
    (This)->lpVtbl -> getLastExcep(This,pExcep)

#define IMTParserLocalizer_get_locale(This,pVal)	\
    (This)->lpVtbl -> get_locale(This,pVal)

#define IMTParserLocalizer_put_locale(This,newVal)	\
    (This)->lpVtbl -> put_locale(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_registerLibrary_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR infoFile);


void __RPC_STUB IMTParserLocalizer_registerLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_setLocale_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR locale);


void __RPC_STUB IMTParserLocalizer_setLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getNbFuncs_Proxy( 
    IMTParserLocalizer * This,
    /* [retval][out] */ int *pNbFuncs);


void __RPC_STUB IMTParserLocalizer_getNbFuncs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getNbOps_Proxy( 
    IMTParserLocalizer * This,
    /* [retval][out] */ int *pNbOps);


void __RPC_STUB IMTParserLocalizer_getNbOps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getNbConsts_Proxy( 
    IMTParserLocalizer * This,
    /* [retval][out] */ int *pNbConsts);


void __RPC_STUB IMTParserLocalizer_getNbConsts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getFuncInfo_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR ID,
    /* [in] */ SMTSyntax *pSyntax,
    /* [retval][out] */ SMTFunction *pInfo);


void __RPC_STUB IMTParserLocalizer_getFuncInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getOpInfo_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR ID,
    /* [retval][out] */ SMTOperator *pInfo);


void __RPC_STUB IMTParserLocalizer_getOpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getConstInfo_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR symbol,
    /* [retval][out] */ SMTConstant *pInfo);


void __RPC_STUB IMTParserLocalizer_getConstInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_formatExcep_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ IMTExcepData *pE,
    /* [in] */ BSTR *msg,
    /* [retval][out] */ BSTR *formattedMsg);


void __RPC_STUB IMTParserLocalizer_formatExcep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_registerAllLibraries_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR directory,
    /* [in] */ BSTR searchPattern);


void __RPC_STUB IMTParserLocalizer_registerAllLibraries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getExcep_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ IMTExcepData *pExcepData,
    /* [retval][out] */ BSTR *pMsg);


void __RPC_STUB IMTParserLocalizer_getExcep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_getLastExcep_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ IMTExcepData *pExcep);


void __RPC_STUB IMTParserLocalizer_getLastExcep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_get_locale_Proxy( 
    IMTParserLocalizer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMTParserLocalizer_get_locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMTParserLocalizer_put_locale_Proxy( 
    IMTParserLocalizer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMTParserLocalizer_put_locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTParserLocalizer_INTERFACE_DEFINED__ */


#ifndef __IMTExcepData_INTERFACE_DEFINED__
#define __IMTExcepData_INTERFACE_DEFINED__

/* interface IMTExcepData */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTExcepData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B75B4C3F-E77A-42DF-8F25-A368DEC37309")
    IMTExcepData : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setNativeData( 
            /* [in] */ int pData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNativeData( 
            /* [retval][out] */ int *pData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getID( 
            /* [retval][out] */ BSTR *pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNbArgs( 
            /* [retval][out] */ LONG *nbArgs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getArgName( 
            /* [in] */ LONG arg,
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getArgVal( 
            /* [in] */ LONG arg,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getDescription( 
            /* [retval][out] */ BSTR *pDesc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setDescription( 
            /* [in] */ BSTR desc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTExcepDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTExcepData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTExcepData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTExcepData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTExcepData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTExcepData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTExcepData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTExcepData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setNativeData )( 
            IMTExcepData * This,
            /* [in] */ int pData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNativeData )( 
            IMTExcepData * This,
            /* [retval][out] */ int *pData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getID )( 
            IMTExcepData * This,
            /* [retval][out] */ BSTR *pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getNbArgs )( 
            IMTExcepData * This,
            /* [retval][out] */ LONG *nbArgs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getArgName )( 
            IMTExcepData * This,
            /* [in] */ LONG arg,
            /* [retval][out] */ BSTR *pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getArgVal )( 
            IMTExcepData * This,
            /* [in] */ LONG arg,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getDescription )( 
            IMTExcepData * This,
            /* [retval][out] */ BSTR *pDesc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setDescription )( 
            IMTExcepData * This,
            /* [in] */ BSTR desc);
        
        END_INTERFACE
    } IMTExcepDataVtbl;

    interface IMTExcepData
    {
        CONST_VTBL struct IMTExcepDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTExcepData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTExcepData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTExcepData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTExcepData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTExcepData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTExcepData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTExcepData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTExcepData_setNativeData(This,pData)	\
    (This)->lpVtbl -> setNativeData(This,pData)

#define IMTExcepData_getNativeData(This,pData)	\
    (This)->lpVtbl -> getNativeData(This,pData)

#define IMTExcepData_getID(This,pID)	\
    (This)->lpVtbl -> getID(This,pID)

#define IMTExcepData_getNbArgs(This,nbArgs)	\
    (This)->lpVtbl -> getNbArgs(This,nbArgs)

#define IMTExcepData_getArgName(This,arg,pName)	\
    (This)->lpVtbl -> getArgName(This,arg,pName)

#define IMTExcepData_getArgVal(This,arg,pVal)	\
    (This)->lpVtbl -> getArgVal(This,arg,pVal)

#define IMTExcepData_getDescription(This,pDesc)	\
    (This)->lpVtbl -> getDescription(This,pDesc)

#define IMTExcepData_setDescription(This,desc)	\
    (This)->lpVtbl -> setDescription(This,desc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_setNativeData_Proxy( 
    IMTExcepData * This,
    /* [in] */ int pData);


void __RPC_STUB IMTExcepData_setNativeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getNativeData_Proxy( 
    IMTExcepData * This,
    /* [retval][out] */ int *pData);


void __RPC_STUB IMTExcepData_getNativeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getID_Proxy( 
    IMTExcepData * This,
    /* [retval][out] */ BSTR *pID);


void __RPC_STUB IMTExcepData_getID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getNbArgs_Proxy( 
    IMTExcepData * This,
    /* [retval][out] */ LONG *nbArgs);


void __RPC_STUB IMTExcepData_getNbArgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getArgName_Proxy( 
    IMTExcepData * This,
    /* [in] */ LONG arg,
    /* [retval][out] */ BSTR *pName);


void __RPC_STUB IMTExcepData_getArgName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getArgVal_Proxy( 
    IMTExcepData * This,
    /* [in] */ LONG arg,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMTExcepData_getArgVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_getDescription_Proxy( 
    IMTExcepData * This,
    /* [retval][out] */ BSTR *pDesc);


void __RPC_STUB IMTExcepData_getDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTExcepData_setDescription_Proxy( 
    IMTExcepData * This,
    /* [in] */ BSTR desc);


void __RPC_STUB IMTExcepData_setDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTExcepData_INTERFACE_DEFINED__ */


#ifndef __IMTDoubleVector_INTERFACE_DEFINED__
#define __IMTDoubleVector_INTERFACE_DEFINED__

/* interface IMTDoubleVector */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMTDoubleVector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("604EB4A2-9CB1-49CC-8AAD-FC33F48A78F4")
    IMTDoubleVector : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValueVector( 
            /* [out][in] */ SAFEARRAY * pValues) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValueVectorVB6( 
            /* [out][in] */ SAFEARRAY * *pValues) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE create( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE registerListener( 
            /* [in] */ int pListener) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE unregisterListener( 
            /* [in] */ int pListener) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTDoubleVectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMTDoubleVector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMTDoubleVector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMTDoubleVector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMTDoubleVector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMTDoubleVector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMTDoubleVector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMTDoubleVector * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setValueVector )( 
            IMTDoubleVector * This,
            /* [out][in] */ SAFEARRAY * pValues);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setValueVectorVB6 )( 
            IMTDoubleVector * This,
            /* [out][in] */ SAFEARRAY * *pValues);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *create )( 
            IMTDoubleVector * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *registerListener )( 
            IMTDoubleVector * This,
            /* [in] */ int pListener);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *unregisterListener )( 
            IMTDoubleVector * This,
            /* [in] */ int pListener);
        
        END_INTERFACE
    } IMTDoubleVectorVtbl;

    interface IMTDoubleVector
    {
        CONST_VTBL struct IMTDoubleVectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTDoubleVector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTDoubleVector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTDoubleVector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTDoubleVector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTDoubleVector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTDoubleVector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTDoubleVector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTDoubleVector_setValueVector(This,pValues)	\
    (This)->lpVtbl -> setValueVector(This,pValues)

#define IMTDoubleVector_setValueVectorVB6(This,pValues)	\
    (This)->lpVtbl -> setValueVectorVB6(This,pValues)

#define IMTDoubleVector_create(This,name)	\
    (This)->lpVtbl -> create(This,name)

#define IMTDoubleVector_registerListener(This,pListener)	\
    (This)->lpVtbl -> registerListener(This,pListener)

#define IMTDoubleVector_unregisterListener(This,pListener)	\
    (This)->lpVtbl -> unregisterListener(This,pListener)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDoubleVector_setValueVector_Proxy( 
    IMTDoubleVector * This,
    /* [out][in] */ SAFEARRAY * pValues);


void __RPC_STUB IMTDoubleVector_setValueVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDoubleVector_setValueVectorVB6_Proxy( 
    IMTDoubleVector * This,
    /* [out][in] */ SAFEARRAY * *pValues);


void __RPC_STUB IMTDoubleVector_setValueVectorVB6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDoubleVector_create_Proxy( 
    IMTDoubleVector * This,
    /* [in] */ BSTR name);


void __RPC_STUB IMTDoubleVector_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDoubleVector_registerListener_Proxy( 
    IMTDoubleVector * This,
    /* [in] */ int pListener);


void __RPC_STUB IMTDoubleVector_registerListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTDoubleVector_unregisterListener_Proxy( 
    IMTDoubleVector * This,
    /* [in] */ int pListener);


void __RPC_STUB IMTDoubleVector_unregisterListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTDoubleVector_INTERFACE_DEFINED__ */



#ifndef __MTPARSERCOMLib_LIBRARY_DEFINED__
#define __MTPARSERCOMLib_LIBRARY_DEFINED__

/* library MTPARSERCOMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MTPARSERCOMLib;

EXTERN_C const CLSID CLSID_MTParser;

#ifdef __cplusplus

class DECLSPEC_UUID("8C49E58A-FFEA-48F0-A42D-68D2FBE14603")
MTParser;
#endif

EXTERN_C const CLSID CLSID_MTDouble;

#ifdef __cplusplus

class DECLSPEC_UUID("0146FD58-5279-4F3F-A70B-77845A2E7B75")
MTDouble;
#endif

EXTERN_C const CLSID CLSID_MTDate;

#ifdef __cplusplus

class DECLSPEC_UUID("39726397-B802-4AB7-90B4-16572007027F")
MTDate;
#endif

EXTERN_C const CLSID CLSID_MTParserLocalizer;

#ifdef __cplusplus

class DECLSPEC_UUID("766FBDFE-9EBB-43BD-BA47-4667B00DD3F9")
MTParserLocalizer;
#endif

EXTERN_C const CLSID CLSID_MTExcepData;

#ifdef __cplusplus

class DECLSPEC_UUID("2B8F32EE-6861-442E-9071-312E93CC4CF0")
MTExcepData;
#endif

EXTERN_C const CLSID CLSID_MTDoubleVector;

#ifdef __cplusplus

class DECLSPEC_UUID("16E097BF-2BC4-4377-9DA1-E2806ACA81C4")
MTDoubleVector;
#endif
#endif /* __MTPARSERCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


