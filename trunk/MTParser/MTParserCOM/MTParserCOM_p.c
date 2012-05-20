

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "MTParserCOM.h"

#define TYPE_FORMAT_STRING_SIZE   1247                              
#define PROC_FORMAT_STRING_SIZE   3427                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTVariable_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTVariable_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTFunction_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTFunction_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTParser_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTParser_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTDouble_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTDouble_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTDate_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTDate_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTParserLocalizer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTParserLocalizer_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTExcepData_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTExcepData_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMTDoubleVector_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMTDoubleVector_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure getSymbol */


	/* Procedure getName */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSymbol */


	/* Parameter pName */

/* 24 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNativeData */


	/* Procedure getNativeVar */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x24 ),	/* 36 */
/* 50 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pData */


	/* Parameter pVar */

/* 60 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getHelpString */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x8 ),	/* 8 */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
/* 86 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 88 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 90 */	NdrFcShort( 0x1 ),	/* 1 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pHelpString */

/* 96 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getID */


	/* Procedure getDescription */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x9 ),	/* 9 */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 126 */	NdrFcShort( 0x1 ),	/* 1 */
/* 128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pID */


	/* Parameter pDescription */

/* 132 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbArgs */


	/* Procedure getNbOps */


	/* Procedure getNbArgs */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0xa ),	/* 10 */
/* 152 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x24 ),	/* 36 */
/* 158 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 160 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nbArgs */


	/* Parameter pNbOps */


	/* Parameter pNbArgs */

/* 168 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate0 */

/* 180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0xb ),	/* 11 */
/* 188 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x2c ),	/* 44 */
/* 194 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 196 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pResult */

/* 204 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 208 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 212 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate1 */

/* 216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 222 */	NdrFcShort( 0xc ),	/* 12 */
/* 224 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 226 */	NdrFcShort( 0x10 ),	/* 16 */
/* 228 */	NdrFcShort( 0x2c ),	/* 44 */
/* 230 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 232 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter arg */

/* 240 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter pResult */

/* 246 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 250 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 254 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate2 */

/* 258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0xd ),	/* 13 */
/* 266 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 268 */	NdrFcShort( 0x20 ),	/* 32 */
/* 270 */	NdrFcShort( 0x2c ),	/* 44 */
/* 272 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 274 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter arg */

/* 282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 284 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 286 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter arg2 */

/* 288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 292 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter pResult */

/* 294 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 296 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 298 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 302 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate3 */

/* 306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0xe ),	/* 14 */
/* 314 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 316 */	NdrFcShort( 0x30 ),	/* 48 */
/* 318 */	NdrFcShort( 0x2c ),	/* 44 */
/* 320 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 322 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter arg */

/* 330 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 332 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 334 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter arg2 */

/* 336 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter arg3 */

/* 342 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 344 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 346 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter pResult */

/* 348 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 350 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 352 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 354 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 356 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate */

/* 360 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 362 */	NdrFcLong( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0xf ),	/* 15 */
/* 368 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x2c ),	/* 44 */
/* 374 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 376 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x12 ),	/* 18 */
/* 382 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pArgs */

/* 384 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 388 */	NdrFcShort( 0x426 ),	/* Type Offset=1062 */

	/* Parameter pResult */

/* 390 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 394 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluateCompiled */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x7 ),	/* 7 */
/* 410 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x2c ),	/* 44 */
/* 416 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 418 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pResult */

/* 426 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 432 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setLocale */


	/* Procedure parseDateTime */


	/* Procedure compile */

/* 438 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 446 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 452 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 454 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x1 ),	/* 1 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter locale */


	/* Parameter datetime */


	/* Parameter expr */

/* 462 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 464 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 466 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluate */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x9 ),	/* 9 */
/* 482 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x2c ),	/* 44 */
/* 488 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 490 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x1 ),	/* 1 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter expr */

/* 498 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 500 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 502 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter pResult */

/* 504 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 506 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 508 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 510 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 512 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineVar */

/* 516 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 518 */	NdrFcLong( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0xa ),	/* 10 */
/* 524 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 530 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 532 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x1 ),	/* 1 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter symbol */

/* 540 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 542 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 544 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 548 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineAllVars */

/* 552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0xb ),	/* 11 */
/* 560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x8 ),	/* 8 */
/* 566 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 568 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure resetExpression */

/* 582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0xc ),	/* 12 */
/* 590 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 596 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure loadPlugin */

/* 612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0xd ),	/* 13 */
/* 620 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 628 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x1 ),	/* 1 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter clsid */

/* 636 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 638 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 640 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 644 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure useLocaleSettings */

/* 648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0xe ),	/* 14 */
/* 656 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 662 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 664 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 672 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 674 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setSyntax */

/* 678 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 680 */	NdrFcLong( 0x0 ),	/* 0 */
/* 684 */	NdrFcShort( 0xf ),	/* 15 */
/* 686 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 688 */	NdrFcShort( 0x2c ),	/* 44 */
/* 690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 692 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 694 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSyntax */

/* 702 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 704 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 706 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Return value */

/* 708 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 710 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSyntax */

/* 714 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 716 */	NdrFcLong( 0x0 ),	/* 0 */
/* 720 */	NdrFcShort( 0x10 ),	/* 16 */
/* 722 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x34 ),	/* 52 */
/* 728 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 730 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 736 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSyntax */

/* 738 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 740 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 742 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Return value */

/* 744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 746 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure defineConst */

/* 750 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x11 ),	/* 17 */
/* 758 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 760 */	NdrFcShort( 0x10 ),	/* 16 */
/* 762 */	NdrFcShort( 0x8 ),	/* 8 */
/* 764 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 766 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	NdrFcShort( 0x1 ),	/* 1 */
/* 772 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 774 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 776 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 778 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter value */

/* 780 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 782 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 784 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 786 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 788 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getParserPtr */

/* 792 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 794 */	NdrFcLong( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x12 ),	/* 18 */
/* 800 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x24 ),	/* 36 */
/* 806 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 808 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pParserPtr */

/* 816 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 818 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 820 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 822 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 824 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure copy */

/* 828 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 830 */	NdrFcLong( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x13 ),	/* 19 */
/* 836 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 844 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pParser */

/* 852 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 854 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 856 */	NdrFcShort( 0x442 ),	/* Type Offset=1090 */

	/* Return value */

/* 858 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 860 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbUsedVars */

/* 864 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 866 */	NdrFcLong( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x14 ),	/* 20 */
/* 872 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x24 ),	/* 36 */
/* 878 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 880 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbUsedVars */

/* 888 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 890 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 892 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 894 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 896 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 898 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getUsedVar */

/* 900 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 902 */	NdrFcLong( 0x0 ),	/* 0 */
/* 906 */	NdrFcShort( 0x15 ),	/* 21 */
/* 908 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 910 */	NdrFcShort( 0x8 ),	/* 8 */
/* 912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 914 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 916 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 918 */	NdrFcShort( 0x1 ),	/* 1 */
/* 920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 924 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 926 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter symbol */

/* 930 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 932 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 934 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 938 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbDefinedConsts */

/* 942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x16 ),	/* 22 */
/* 950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x24 ),	/* 36 */
/* 956 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbDefinedConsts */

/* 966 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getConst */

/* 978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x17 ),	/* 23 */
/* 986 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 988 */	NdrFcShort( 0x8 ),	/* 8 */
/* 990 */	NdrFcShort( 0x8 ),	/* 8 */
/* 992 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 994 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 996 */	NdrFcShort( 0x2 ),	/* 2 */
/* 998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1002 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pConst */

/* 1008 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1012 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 1014 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1016 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbDefinedFuncs */

/* 1020 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1022 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1028 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1034 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1036 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbDefinedFuncs */

/* 1044 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1050 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1052 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getFunc */

/* 1056 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1058 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1064 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1068 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1070 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1072 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1074 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1080 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1082 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pFunc */

/* 1086 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1088 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1090 */	NdrFcShort( 0x470 ),	/* Type Offset=1136 */

	/* Return value */

/* 1092 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1094 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1096 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbDefinedOps */

/* 1098 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1100 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1106 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1110 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1112 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1114 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbDefinedOps */

/* 1122 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1124 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1128 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1130 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getOp */

/* 1134 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1142 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1148 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1150 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1152 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1158 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1160 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pOp */

/* 1164 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1166 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1168 */	NdrFcShort( 0x470 ),	/* Type Offset=1136 */

	/* Return value */

/* 1170 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1172 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLastExcep */

/* 1176 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1182 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1184 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1188 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1190 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1192 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1198 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pExcep */

/* 1200 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1202 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1204 */	NdrFcShort( 0x48a ),	/* Type Offset=1162 */

	/* Return value */

/* 1206 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1208 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure defineVar */

/* 1212 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1220 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1224 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1226 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1228 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1234 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVar */

/* 1236 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1238 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1240 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */

	/* Return value */

/* 1242 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1244 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNaN */

/* 1248 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1250 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1254 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1256 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1260 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1262 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1264 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1270 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNaN */

/* 1272 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1274 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1276 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1278 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1280 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure isNaN */

/* 1284 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1290 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1292 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1296 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1298 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1300 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pRet */

/* 1308 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1310 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1312 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1314 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1316 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1318 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure defineMacro */

/* 1320 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1322 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1326 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1328 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1332 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1334 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1336 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1340 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1342 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter prototype */

/* 1344 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1346 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1348 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter macro */

/* 1350 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1352 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1354 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter description */

/* 1356 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1358 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1360 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1364 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure isFinite */

/* 1368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1374 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1376 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1382 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1384 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pRet */

/* 1392 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1394 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1398 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1400 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure loadAllPlugins */

/* 1404 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1406 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1410 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1412 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1418 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1420 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1424 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1426 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter directory */

/* 1428 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1430 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1432 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter searchPattern */

/* 1434 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1436 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1438 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1440 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1442 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1444 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluateCompiledBatch */

/* 1446 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1448 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1452 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1454 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1456 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1458 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1460 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1462 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1464 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1466 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nbLoops */

/* 1470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1472 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pResults */

/* 1476 */	NdrFcShort( 0x9b ),	/* Flags:  must size, must free, in, out, by val, */
/* 1478 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1480 */	NdrFcShort( 0x4b6 ),	/* Type Offset=1206 */

	/* Return value */

/* 1482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure redefineVar */

/* 1488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1496 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1502 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1504 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1510 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVar */

/* 1512 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1516 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */

	/* Return value */

/* 1518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1520 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_expression */

/* 1524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1538 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1540 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1542 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1548 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1552 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_expression */

/* 1560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1574 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1576 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1582 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1584 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1588 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_autoVarDefinitionEnabled */

/* 1596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1604 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1608 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1610 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1612 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1618 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1620 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1624 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1628 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_autoVarDefinitionEnabled */

/* 1632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1640 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1642 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1646 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1648 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1656 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1660 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_syntax */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1676 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1682 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1684 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1692 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Return value */

/* 1698 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_syntax */

/* 1704 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1706 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1712 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1714 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1718 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1720 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1726 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1728 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 1730 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1732 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Return value */

/* 1734 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineConst */

/* 1740 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1742 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1748 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1754 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1756 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1760 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1762 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 1764 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1766 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1768 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1770 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1772 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1774 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineFuncById */

/* 1776 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1778 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1782 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1784 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1788 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1790 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1792 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1798 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter id */

/* 1800 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1802 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1804 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1808 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineOpById */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1820 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1828 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1832 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter id */

/* 1836 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1840 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1842 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1844 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1846 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineFuncsBySymbol */

/* 1848 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1850 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1856 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1862 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1864 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1870 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter symbol */

/* 1872 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1874 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1876 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1878 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1880 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure undefineOpsBySymbol */

/* 1884 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1890 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1898 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1900 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1904 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter symbol */

/* 1908 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1910 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1912 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1916 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbDefinedVars */

/* 1920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1926 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1928 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1932 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1934 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1936 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1942 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbDefinedOps */

/* 1944 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1946 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1952 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getVar */

/* 1956 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1964 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1966 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1970 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1972 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1974 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1978 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1980 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1982 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1984 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter symbol */

/* 1986 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1988 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1990 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1992 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1994 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure defineFunc */

/* 1998 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2000 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x32 ),	/* 50 */
/* 2006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2012 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2014 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFunc */

/* 2022 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2024 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2026 */	NdrFcShort( 0x4c4 ),	/* Type Offset=1220 */

	/* Return value */

/* 2028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2030 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure evaluateCompiledBatchVB6 */

/* 2034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x33 ),	/* 51 */
/* 2042 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2048 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2050 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2052 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2054 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2056 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nbLoops */

/* 2058 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2060 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pResults */

/* 2064 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 2066 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2068 */	NdrFcShort( 0x4b6 ),	/* Type Offset=1206 */

	/* Return value */

/* 2070 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2072 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2074 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure create */

/* 2076 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2078 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2082 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2084 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2086 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2088 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2090 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2092 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2096 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 2100 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2104 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter value */

/* 2106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2110 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2112 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2114 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_value */

/* 2118 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2120 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2126 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2130 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2132 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2134 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2140 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2142 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2144 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2146 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2148 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2150 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2152 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_value */

/* 2154 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2156 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2160 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2162 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2164 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2166 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2168 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2170 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2178 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2180 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2182 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2186 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_name */

/* 2190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2196 */	NdrFcShort( 0xa ),	/* 10 */
/* 2198 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2204 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2206 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2208 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2212 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2214 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2216 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2218 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2220 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2222 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2224 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setValue */

/* 2226 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2228 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2232 */	NdrFcShort( 0xb ),	/* 11 */
/* 2234 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2236 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2240 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2242 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2248 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter value */

/* 2250 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2252 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2254 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2256 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2258 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_value */


	/* Procedure getValue */

/* 2262 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2268 */	NdrFcShort( 0xc ),	/* 12 */
/* 2270 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2274 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2276 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2278 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2284 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pValue */

/* 2286 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2288 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2290 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2292 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2294 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure registerLibrary */


	/* Procedure create */

/* 2298 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2300 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2304 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2306 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2312 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2314 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2318 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2320 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter infoFile */


	/* Parameter name */

/* 2322 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2324 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2326 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */


	/* Return value */

/* 2328 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2330 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setDate */

/* 2334 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2340 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2342 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2344 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2346 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2348 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 2350 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2356 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter year */

/* 2358 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter month */

/* 2364 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter day */

/* 2370 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2378 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setTime */

/* 2382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2388 */	NdrFcShort( 0xa ),	/* 10 */
/* 2390 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2392 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2396 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 2398 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2404 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hour */

/* 2406 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2408 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter minute */

/* 2412 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2414 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter second */

/* 2418 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2420 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2426 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_name */

/* 2430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2436 */	NdrFcShort( 0xb ),	/* 11 */
/* 2438 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2442 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2444 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2446 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2448 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2452 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2454 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2456 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2458 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2462 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_value */

/* 2466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2472 */	NdrFcShort( 0xd ),	/* 13 */
/* 2474 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2476 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2480 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2482 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2490 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2492 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2494 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2498 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure format */

/* 2502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2508 */	NdrFcShort( 0xe ),	/* 14 */
/* 2510 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2516 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2518 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2520 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDateStr */

/* 2526 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2530 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setValue */

/* 2538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2544 */	NdrFcShort( 0xf ),	/* 15 */
/* 2546 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2548 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2552 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2554 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter value */

/* 2562 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2564 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2566 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2568 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2570 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getValue */

/* 2574 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2580 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2582 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2586 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2588 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2590 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pValue */

/* 2598 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2600 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2602 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2604 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2606 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbFuncs */

/* 2610 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2612 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2616 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2618 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2622 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2624 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2626 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbFuncs */

/* 2634 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2636 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2640 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2642 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNbConsts */

/* 2646 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2648 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2652 */	NdrFcShort( 0xb ),	/* 11 */
/* 2654 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2658 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2660 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2662 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2668 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNbConsts */

/* 2670 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2672 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2674 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2676 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2678 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2680 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getFuncInfo */

/* 2682 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2684 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2688 */	NdrFcShort( 0xc ),	/* 12 */
/* 2690 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2692 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2694 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2696 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2698 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2702 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2704 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 2706 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2708 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2710 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter pSyntax */

/* 2712 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 2714 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2716 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Parameter pInfo */

/* 2718 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2720 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2722 */	NdrFcShort( 0x470 ),	/* Type Offset=1136 */

	/* Return value */

/* 2724 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2726 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2728 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getOpInfo */

/* 2730 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2732 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2736 */	NdrFcShort( 0xd ),	/* 13 */
/* 2738 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2742 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2744 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2746 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2748 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2750 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 2754 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2756 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2758 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter pInfo */

/* 2760 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2762 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2764 */	NdrFcShort( 0x470 ),	/* Type Offset=1136 */

	/* Return value */

/* 2766 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2768 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2770 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getConstInfo */

/* 2772 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2774 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2778 */	NdrFcShort( 0xe ),	/* 14 */
/* 2780 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2786 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2788 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2790 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2792 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter symbol */

/* 2796 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2798 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2800 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter pInfo */

/* 2802 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2804 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2806 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 2808 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2810 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2812 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure formatExcep */

/* 2814 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2816 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2820 */	NdrFcShort( 0xf ),	/* 15 */
/* 2822 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2828 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2830 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2832 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2834 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2836 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pE */

/* 2838 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2840 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2842 */	NdrFcShort( 0x48a ),	/* Type Offset=1162 */

	/* Parameter msg */

/* 2844 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2846 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2848 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter formattedMsg */

/* 2850 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2854 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2856 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2858 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2860 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure registerAllLibraries */

/* 2862 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2864 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2868 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2870 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2876 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2878 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2882 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2884 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter directory */

/* 2886 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2888 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2890 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Parameter searchPattern */

/* 2892 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2894 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2896 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 2898 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2900 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2902 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getExcep */

/* 2904 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2906 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2910 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2912 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2916 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2918 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2920 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2922 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2926 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pExcepData */

/* 2928 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2930 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2932 */	NdrFcShort( 0x48a ),	/* Type Offset=1162 */

	/* Parameter pMsg */

/* 2934 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2936 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2938 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2940 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2942 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2944 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLastExcep */

/* 2946 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2948 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2952 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2954 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2958 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2960 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2962 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2966 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2968 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pExcep */

/* 2970 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2972 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2974 */	NdrFcShort( 0x48a ),	/* Type Offset=1162 */

	/* Return value */

/* 2976 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2978 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2980 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_locale */

/* 2982 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2984 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2988 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2990 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2994 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2996 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2998 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3000 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3004 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3006 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3008 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3010 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3012 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3014 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_locale */

/* 3018 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3020 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3024 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3026 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3032 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3034 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3038 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3040 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3042 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3044 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3046 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 3048 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3050 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3052 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setNativeData */

/* 3054 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3056 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3060 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3062 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3064 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3068 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3070 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3076 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pData */

/* 3078 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3080 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3084 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3086 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3088 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getArgName */

/* 3090 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3092 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3096 */	NdrFcShort( 0xb ),	/* 11 */
/* 3098 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3100 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3104 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3106 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3108 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter arg */

/* 3114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3116 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pName */

/* 3120 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3122 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3124 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3128 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getArgVal */

/* 3132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3138 */	NdrFcShort( 0xc ),	/* 12 */
/* 3140 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3146 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3148 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3150 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter arg */

/* 3156 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3162 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3164 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3166 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3170 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getDescription */

/* 3174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3180 */	NdrFcShort( 0xd ),	/* 13 */
/* 3182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3188 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3190 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3192 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3196 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDesc */

/* 3198 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3200 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3202 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3206 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setDescription */

/* 3210 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3212 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3216 */	NdrFcShort( 0xe ),	/* 14 */
/* 3218 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3222 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3224 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3226 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3230 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3232 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter desc */

/* 3234 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3236 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3238 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 3240 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3242 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setValueVector */

/* 3246 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3248 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3252 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3254 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3258 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3260 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3262 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3264 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3266 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3268 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pValues */

/* 3270 */	NdrFcShort( 0x9b ),	/* Flags:  must size, must free, in, out, by val, */
/* 3272 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3274 */	NdrFcShort( 0x4b6 ),	/* Type Offset=1206 */

	/* Return value */

/* 3276 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3278 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setValueVectorVB6 */

/* 3282 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3288 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3292 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3294 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3296 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3298 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3300 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3302 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3304 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pValues */

/* 3306 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 3308 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3310 */	NdrFcShort( 0x4b6 ),	/* Type Offset=1206 */

	/* Return value */

/* 3312 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3314 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3316 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure create */

/* 3318 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3320 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3324 */	NdrFcShort( 0x9 ),	/* 9 */
/* 3326 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3330 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3332 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3334 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3338 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3340 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 3342 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3344 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3346 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 3348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3350 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure registerListener */

/* 3354 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3360 */	NdrFcShort( 0xa ),	/* 10 */
/* 3362 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3366 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3368 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3370 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3376 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pListener */

/* 3378 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3380 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3384 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3386 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure unregisterListener */

/* 3390 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3392 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0xb ),	/* 11 */
/* 3398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3400 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3404 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3406 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3412 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pListener */

/* 3414 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3416 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3420 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3422 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 44 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 46 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 48 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 50 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 52 */	NdrFcShort( 0x2 ),	/* Offset= 2 (54) */
/* 54 */	
			0x12, 0x0,	/* FC_UP */
/* 56 */	NdrFcShort( 0x3dc ),	/* Offset= 988 (1044) */
/* 58 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 60 */	NdrFcShort( 0x18 ),	/* 24 */
/* 62 */	NdrFcShort( 0xa ),	/* 10 */
/* 64 */	NdrFcLong( 0x8 ),	/* 8 */
/* 68 */	NdrFcShort( 0x5a ),	/* Offset= 90 (158) */
/* 70 */	NdrFcLong( 0xd ),	/* 13 */
/* 74 */	NdrFcShort( 0x90 ),	/* Offset= 144 (218) */
/* 76 */	NdrFcLong( 0x9 ),	/* 9 */
/* 80 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (274) */
/* 82 */	NdrFcLong( 0xc ),	/* 12 */
/* 86 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (790) */
/* 88 */	NdrFcLong( 0x24 ),	/* 36 */
/* 92 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (838) */
/* 94 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 98 */	NdrFcShort( 0x306 ),	/* Offset= 774 (872) */
/* 100 */	NdrFcLong( 0x10 ),	/* 16 */
/* 104 */	NdrFcShort( 0x320 ),	/* Offset= 800 (904) */
/* 106 */	NdrFcLong( 0x2 ),	/* 2 */
/* 110 */	NdrFcShort( 0x33a ),	/* Offset= 826 (936) */
/* 112 */	NdrFcLong( 0x3 ),	/* 3 */
/* 116 */	NdrFcShort( 0x354 ),	/* Offset= 852 (968) */
/* 118 */	NdrFcLong( 0x14 ),	/* 20 */
/* 122 */	NdrFcShort( 0x36e ),	/* Offset= 878 (1000) */
/* 124 */	NdrFcShort( 0xffff ),	/* Offset= -1 (123) */
/* 126 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 128 */	NdrFcShort( 0x4 ),	/* 4 */
/* 130 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 136 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 138 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 140 */	NdrFcShort( 0x4 ),	/* 4 */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x1 ),	/* 1 */
/* 146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	0x12, 0x0,	/* FC_UP */
/* 152 */	NdrFcShort( 0xff7e ),	/* Offset= -130 (22) */
/* 154 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 156 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 158 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 160 */	NdrFcShort( 0x8 ),	/* 8 */
/* 162 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 164 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 166 */	NdrFcShort( 0x4 ),	/* 4 */
/* 168 */	NdrFcShort( 0x4 ),	/* 4 */
/* 170 */	0x11, 0x0,	/* FC_RP */
/* 172 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (126) */
/* 174 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 176 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 178 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 188 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 190 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 192 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 194 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 196 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 206 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 210 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 212 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 214 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (178) */
/* 216 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 218 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x6 ),	/* Offset= 6 (230) */
/* 226 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 228 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 230 */	
			0x11, 0x0,	/* FC_RP */
/* 232 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (196) */
/* 234 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 236 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 246 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 248 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 250 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 252 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 256 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 262 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 266 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 268 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 270 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (234) */
/* 272 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 274 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 276 */	NdrFcShort( 0x8 ),	/* 8 */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x6 ),	/* Offset= 6 (286) */
/* 282 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 284 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 286 */	
			0x11, 0x0,	/* FC_RP */
/* 288 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (252) */
/* 290 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 292 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 294 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 296 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 298 */	NdrFcShort( 0x2 ),	/* Offset= 2 (300) */
/* 300 */	NdrFcShort( 0x10 ),	/* 16 */
/* 302 */	NdrFcShort( 0x2f ),	/* 47 */
/* 304 */	NdrFcLong( 0x14 ),	/* 20 */
/* 308 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 310 */	NdrFcLong( 0x3 ),	/* 3 */
/* 314 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 316 */	NdrFcLong( 0x11 ),	/* 17 */
/* 320 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 322 */	NdrFcLong( 0x2 ),	/* 2 */
/* 326 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 328 */	NdrFcLong( 0x4 ),	/* 4 */
/* 332 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 334 */	NdrFcLong( 0x5 ),	/* 5 */
/* 338 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 340 */	NdrFcLong( 0xb ),	/* 11 */
/* 344 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 346 */	NdrFcLong( 0xa ),	/* 10 */
/* 350 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 352 */	NdrFcLong( 0x6 ),	/* 6 */
/* 356 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (588) */
/* 358 */	NdrFcLong( 0x7 ),	/* 7 */
/* 362 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 364 */	NdrFcLong( 0x8 ),	/* 8 */
/* 368 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (594) */
/* 370 */	NdrFcLong( 0xd ),	/* 13 */
/* 374 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (178) */
/* 376 */	NdrFcLong( 0x9 ),	/* 9 */
/* 380 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (234) */
/* 382 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 386 */	NdrFcShort( 0xd4 ),	/* Offset= 212 (598) */
/* 388 */	NdrFcLong( 0x24 ),	/* 36 */
/* 392 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (606) */
/* 394 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 398 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (606) */
/* 400 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 404 */	NdrFcShort( 0x100 ),	/* Offset= 256 (660) */
/* 406 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 410 */	NdrFcShort( 0xfe ),	/* Offset= 254 (664) */
/* 412 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 416 */	NdrFcShort( 0xfc ),	/* Offset= 252 (668) */
/* 418 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 422 */	NdrFcShort( 0xfa ),	/* Offset= 250 (672) */
/* 424 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 428 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (676) */
/* 430 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 434 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (680) */
/* 436 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 440 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (664) */
/* 442 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 446 */	NdrFcShort( 0xde ),	/* Offset= 222 (668) */
/* 448 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 452 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (684) */
/* 454 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 458 */	NdrFcShort( 0xde ),	/* Offset= 222 (680) */
/* 460 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 464 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (688) */
/* 466 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 470 */	NdrFcShort( 0xde ),	/* Offset= 222 (692) */
/* 472 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 476 */	NdrFcShort( 0xdc ),	/* Offset= 220 (696) */
/* 478 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 482 */	NdrFcShort( 0xda ),	/* Offset= 218 (700) */
/* 484 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 488 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (712) */
/* 490 */	NdrFcLong( 0x10 ),	/* 16 */
/* 494 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 496 */	NdrFcLong( 0x12 ),	/* 18 */
/* 500 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 502 */	NdrFcLong( 0x13 ),	/* 19 */
/* 506 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 508 */	NdrFcLong( 0x15 ),	/* 21 */
/* 512 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 514 */	NdrFcLong( 0x16 ),	/* 22 */
/* 518 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 520 */	NdrFcLong( 0x17 ),	/* 23 */
/* 524 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 526 */	NdrFcLong( 0xe ),	/* 14 */
/* 530 */	NdrFcShort( 0xbe ),	/* Offset= 190 (720) */
/* 532 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 536 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (730) */
/* 538 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 542 */	NdrFcShort( 0xc0 ),	/* Offset= 192 (734) */
/* 544 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 548 */	NdrFcShort( 0x74 ),	/* Offset= 116 (664) */
/* 550 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 554 */	NdrFcShort( 0x72 ),	/* Offset= 114 (668) */
/* 556 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 560 */	NdrFcShort( 0x70 ),	/* Offset= 112 (672) */
/* 562 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 566 */	NdrFcShort( 0x66 ),	/* Offset= 102 (668) */
/* 568 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 572 */	NdrFcShort( 0x60 ),	/* Offset= 96 (668) */
/* 574 */	NdrFcLong( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x0 ),	/* Offset= 0 (578) */
/* 580 */	NdrFcLong( 0x1 ),	/* 1 */
/* 584 */	NdrFcShort( 0x0 ),	/* Offset= 0 (584) */
/* 586 */	NdrFcShort( 0xffff ),	/* Offset= -1 (585) */
/* 588 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 592 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 594 */	
			0x12, 0x0,	/* FC_UP */
/* 596 */	NdrFcShort( 0xfdc2 ),	/* Offset= -574 (22) */
/* 598 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 600 */	NdrFcShort( 0x2 ),	/* Offset= 2 (602) */
/* 602 */	
			0x12, 0x0,	/* FC_UP */
/* 604 */	NdrFcShort( 0x1b8 ),	/* Offset= 440 (1044) */
/* 606 */	
			0x12, 0x0,	/* FC_UP */
/* 608 */	NdrFcShort( 0x20 ),	/* Offset= 32 (640) */
/* 610 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 612 */	NdrFcLong( 0x2f ),	/* 47 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 622 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 624 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 626 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 628 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 632 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 634 */	NdrFcShort( 0x4 ),	/* 4 */
/* 636 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 638 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 640 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 642 */	NdrFcShort( 0x10 ),	/* 16 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0xa ),	/* Offset= 10 (656) */
/* 648 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 650 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 652 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (610) */
/* 654 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 656 */	
			0x12, 0x0,	/* FC_UP */
/* 658 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (628) */
/* 660 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 662 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 664 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 666 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 668 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 670 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 672 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 674 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 676 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 678 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 680 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 682 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 684 */	
			0x12, 0x0,	/* FC_UP */
/* 686 */	NdrFcShort( 0xff9e ),	/* Offset= -98 (588) */
/* 688 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 690 */	NdrFcShort( 0xffa0 ),	/* Offset= -96 (594) */
/* 692 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 694 */	NdrFcShort( 0xfdfc ),	/* Offset= -516 (178) */
/* 696 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 698 */	NdrFcShort( 0xfe30 ),	/* Offset= -464 (234) */
/* 700 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 702 */	NdrFcShort( 0x2 ),	/* Offset= 2 (704) */
/* 704 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 706 */	NdrFcShort( 0x2 ),	/* Offset= 2 (708) */
/* 708 */	
			0x12, 0x0,	/* FC_UP */
/* 710 */	NdrFcShort( 0x14e ),	/* Offset= 334 (1044) */
/* 712 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 714 */	NdrFcShort( 0x2 ),	/* Offset= 2 (716) */
/* 716 */	
			0x12, 0x0,	/* FC_UP */
/* 718 */	NdrFcShort( 0x14 ),	/* Offset= 20 (738) */
/* 720 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 722 */	NdrFcShort( 0x10 ),	/* 16 */
/* 724 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 726 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 728 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 730 */	
			0x12, 0x0,	/* FC_UP */
/* 732 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (720) */
/* 734 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 736 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 738 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 740 */	NdrFcShort( 0x20 ),	/* 32 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x0 ),	/* Offset= 0 (744) */
/* 746 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 748 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 750 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 752 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 754 */	NdrFcShort( 0xfe30 ),	/* Offset= -464 (290) */
/* 756 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 758 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 768 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 770 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 772 */	NdrFcShort( 0x4 ),	/* 4 */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x1 ),	/* 1 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	0x12, 0x0,	/* FC_UP */
/* 784 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (738) */
/* 786 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 788 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 790 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 792 */	NdrFcShort( 0x8 ),	/* 8 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0x6 ),	/* Offset= 6 (802) */
/* 798 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 800 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 802 */	
			0x11, 0x0,	/* FC_RP */
/* 804 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (758) */
/* 806 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 808 */	NdrFcShort( 0x4 ),	/* 4 */
/* 810 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 816 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 818 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 824 */	NdrFcShort( 0x1 ),	/* 1 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	0x12, 0x0,	/* FC_UP */
/* 832 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (640) */
/* 834 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 836 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 838 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x6 ),	/* Offset= 6 (850) */
/* 846 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 848 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 850 */	
			0x11, 0x0,	/* FC_RP */
/* 852 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (806) */
/* 854 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 860 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x10 ),	/* 16 */
/* 864 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 866 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 868 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (854) */
			0x5b,		/* FC_END */
/* 872 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x18 ),	/* 24 */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0xa ),	/* Offset= 10 (888) */
/* 880 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 882 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 884 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (860) */
/* 886 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 888 */	
			0x11, 0x0,	/* FC_RP */
/* 890 */	NdrFcShort( 0xfd4a ),	/* Offset= -694 (196) */
/* 892 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 894 */	NdrFcShort( 0x1 ),	/* 1 */
/* 896 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 900 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 902 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	0x12, 0x0,	/* FC_UP */
/* 918 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (892) */
/* 920 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 922 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 924 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 926 */	NdrFcShort( 0x2 ),	/* 2 */
/* 928 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 934 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 936 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 940 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 944 */	NdrFcShort( 0x4 ),	/* 4 */
/* 946 */	NdrFcShort( 0x4 ),	/* 4 */
/* 948 */	0x12, 0x0,	/* FC_UP */
/* 950 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (924) */
/* 952 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 954 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 956 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 958 */	NdrFcShort( 0x4 ),	/* 4 */
/* 960 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 966 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 968 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 972 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 974 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 976 */	NdrFcShort( 0x4 ),	/* 4 */
/* 978 */	NdrFcShort( 0x4 ),	/* 4 */
/* 980 */	0x12, 0x0,	/* FC_UP */
/* 982 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (956) */
/* 984 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 986 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 988 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 990 */	NdrFcShort( 0x8 ),	/* 8 */
/* 992 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 998 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1000 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1002 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1004 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1006 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1008 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1010 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1012 */	0x12, 0x0,	/* FC_UP */
/* 1014 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (988) */
/* 1016 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1018 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1020 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1022 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1024 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1026 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1028 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1032 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1034 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1036 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1038 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1040 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1020) */
/* 1042 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1044 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1046 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1048 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1028) */
/* 1050 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1050) */
/* 1052 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1054 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1056 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1058 */	NdrFcShort( 0xfc18 ),	/* Offset= -1000 (58) */
/* 1060 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1062 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1064 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1066 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1070 */	NdrFcShort( 0xfc04 ),	/* Offset= -1020 (50) */
/* 1072 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1080 */	NdrFcShort( 0xfe1a ),	/* Offset= -486 (594) */
/* 1082 */	
			0x11, 0x0,	/* FC_RP */
/* 1084 */	NdrFcShort( 0xffc0 ),	/* Offset= -64 (1020) */
/* 1086 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1088 */	NdrFcShort( 0xffbc ),	/* Offset= -68 (1020) */
/* 1090 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1092 */	NdrFcLong( 0xab830d10 ),	/* -1417474800 */
/* 1096 */	NdrFcShort( 0x490e ),	/* 18702 */
/* 1098 */	NdrFcShort( 0x4228 ),	/* 16936 */
/* 1100 */	0xae,		/* 174 */
			0x23,		/* 35 */
/* 1102 */	0x1,		/* 1 */
			0xc7,		/* 199 */
/* 1104 */	0x94,		/* 148 */
			0xe5,		/* 229 */
/* 1106 */	0xc0,		/* 192 */
			0x36,		/* 54 */
/* 1108 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1110 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1112) */
/* 1112 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1114 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1118 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1118) */
/* 1120 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1122 */	NdrFcShort( 0xfbbe ),	/* Offset= -1090 (32) */
/* 1124 */	0x40,		/* FC_STRUCTPAD4 */
			0xc,		/* FC_DOUBLE */
/* 1126 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1128 */	NdrFcShort( 0xfbb8 ),	/* Offset= -1096 (32) */
/* 1130 */	0x40,		/* FC_STRUCTPAD4 */
			0x5b,		/* FC_END */
/* 1132 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1134 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1136) */
/* 1136 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1138 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1142) */
/* 1144 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1146 */	NdrFcShort( 0xfba6 ),	/* Offset= -1114 (32) */
/* 1148 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1150 */	NdrFcShort( 0xfba2 ),	/* Offset= -1118 (32) */
/* 1152 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1154 */	NdrFcShort( 0xfb9e ),	/* Offset= -1122 (32) */
/* 1156 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1158 */	NdrFcShort( 0xfb9a ),	/* Offset= -1126 (32) */
/* 1160 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1162 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1164 */	NdrFcLong( 0xb75b4c3f ),	/* -1218753473 */
/* 1168 */	NdrFcShort( 0xe77a ),	/* -6278 */
/* 1170 */	NdrFcShort( 0x42df ),	/* 17119 */
/* 1172 */	0x8f,		/* 143 */
			0x25,		/* 37 */
/* 1174 */	0xa3,		/* 163 */
			0x68,		/* 104 */
/* 1176 */	0xde,		/* 222 */
			0xc3,		/* 195 */
/* 1178 */	0x73,		/* 115 */
			0x9,		/* 9 */
/* 1180 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1182 */	NdrFcLong( 0xac930f10 ),	/* -1399648496 */
/* 1186 */	NdrFcShort( 0x590e ),	/* 22798 */
/* 1188 */	NdrFcShort( 0x5928 ),	/* 22824 */
/* 1190 */	0xbe,		/* 190 */
			0x23,		/* 35 */
/* 1192 */	0x12,		/* 18 */
			0xc6,		/* 198 */
/* 1194 */	0x94,		/* 148 */
			0xd5,		/* 213 */
/* 1196 */	0xb0,		/* 176 */
			0x35,		/* 53 */
/* 1198 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1200 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1202) */
/* 1202 */	
			0x13, 0x0,	/* FC_OP */
/* 1204 */	NdrFcShort( 0xff60 ),	/* Offset= -160 (1044) */
/* 1206 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1208 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1210 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1214 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1198) */
/* 1216 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1218 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1220 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1222 */	NdrFcLong( 0xed930f11 ),	/* -309129455 */
/* 1226 */	NdrFcShort( 0x520e ),	/* 21006 */
/* 1228 */	NdrFcShort( 0x5926 ),	/* 22822 */
/* 1230 */	0xbe,		/* 190 */
			0x23,		/* 35 */
/* 1232 */	0x12,		/* 18 */
			0xc6,		/* 198 */
/* 1234 */	0x94,		/* 148 */
			0xd5,		/* 213 */
/* 1236 */	0xb0,		/* 176 */
			0x35,		/* 53 */
/* 1238 */	
			0x11, 0x0,	/* FC_RP */
/* 1240 */	NdrFcShort( 0xffde ),	/* Offset= -34 (1206) */
/* 1242 */	
			0x11, 0x0,	/* FC_RP */
/* 1244 */	NdrFcShort( 0xff54 ),	/* Offset= -172 (1072) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };



/* Standard interface: __MIDL_itf_MTParserCOM_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMTVariable, ver. 0.0,
   GUID={0xAC930F10,0x590E,0x5928,{0xBE,0x23,0x12,0xC6,0x94,0xD5,0xB0,0x35}} */

#pragma code_seg(".orpc")
static const unsigned short IMTVariable_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36
    };

static const MIDL_STUBLESS_PROXY_INFO IMTVariable_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTVariable_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTVariable_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTVariable_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IMTVariableProxyVtbl = 
{
    &IMTVariable_ProxyInfo,
    &IID_IMTVariable,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTVariable::getName */ ,
    (void *) (INT_PTR) -1 /* IMTVariable::getNativeVar */
};


static const PRPC_STUB_FUNCTION IMTVariable_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTVariableStubVtbl =
{
    &IID_IMTVariable,
    &IMTVariable_ServerInfo,
    9,
    &IMTVariable_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTFunction, ver. 0.0,
   GUID={0xED930F11,0x520E,0x5926,{0xBE,0x23,0x12,0xC6,0x94,0xD5,0xB0,0x35}} */

#pragma code_seg(".orpc")
static const unsigned short IMTFunction_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    72,
    108,
    144,
    180,
    216,
    258,
    306,
    360
    };

static const MIDL_STUBLESS_PROXY_INFO IMTFunction_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTFunction_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTFunction_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTFunction_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IMTFunctionProxyVtbl = 
{
    &IMTFunction_ProxyInfo,
    &IID_IMTFunction,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::getSymbol */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::getHelpString */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::getDescription */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::getNbArgs */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::evaluate0 */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::evaluate1 */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::evaluate2 */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::evaluate3 */ ,
    (void *) (INT_PTR) -1 /* IMTFunction::evaluate */
};


static const PRPC_STUB_FUNCTION IMTFunction_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTFunctionStubVtbl =
{
    &IID_IMTFunction,
    &IMTFunction_ServerInfo,
    16,
    &IMTFunction_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTParser, ver. 0.0,
   GUID={0xAB830D10,0x490E,0x4228,{0xAE,0x23,0x01,0xC7,0x94,0xE5,0xC0,0x36}} */

#pragma code_seg(".orpc")
static const unsigned short IMTParser_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    402,
    438,
    474,
    516,
    552,
    582,
    612,
    648,
    678,
    714,
    750,
    792,
    828,
    864,
    900,
    942,
    978,
    1020,
    1056,
    1098,
    1134,
    1176,
    1212,
    1248,
    1284,
    1320,
    1368,
    1404,
    1446,
    1488,
    1524,
    1560,
    1596,
    1632,
    1668,
    1704,
    1740,
    1776,
    1812,
    1848,
    1884,
    1920,
    1956,
    1998,
    2034
    };

static const MIDL_STUBLESS_PROXY_INFO IMTParser_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTParser_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTParser_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTParser_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(52) _IMTParserProxyVtbl = 
{
    &IMTParser_ProxyInfo,
    &IID_IMTParser,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTParser::evaluateCompiled */ ,
    (void *) (INT_PTR) -1 /* IMTParser::compile */ ,
    (void *) (INT_PTR) -1 /* IMTParser::evaluate */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineVar */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineAllVars */ ,
    (void *) (INT_PTR) -1 /* IMTParser::resetExpression */ ,
    (void *) (INT_PTR) -1 /* IMTParser::loadPlugin */ ,
    (void *) (INT_PTR) -1 /* IMTParser::useLocaleSettings */ ,
    (void *) (INT_PTR) -1 /* IMTParser::setSyntax */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getSyntax */ ,
    (void *) (INT_PTR) -1 /* IMTParser::defineConst */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getParserPtr */ ,
    (void *) (INT_PTR) -1 /* IMTParser::copy */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNbUsedVars */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getUsedVar */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNbDefinedConsts */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getConst */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNbDefinedFuncs */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getFunc */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNbDefinedOps */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getOp */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getLastExcep */ ,
    (void *) (INT_PTR) -1 /* IMTParser::defineVar */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNaN */ ,
    (void *) (INT_PTR) -1 /* IMTParser::isNaN */ ,
    (void *) (INT_PTR) -1 /* IMTParser::defineMacro */ ,
    (void *) (INT_PTR) -1 /* IMTParser::isFinite */ ,
    (void *) (INT_PTR) -1 /* IMTParser::loadAllPlugins */ ,
    (void *) (INT_PTR) -1 /* IMTParser::evaluateCompiledBatch */ ,
    (void *) (INT_PTR) -1 /* IMTParser::redefineVar */ ,
    (void *) (INT_PTR) -1 /* IMTParser::get_expression */ ,
    (void *) (INT_PTR) -1 /* IMTParser::put_expression */ ,
    (void *) (INT_PTR) -1 /* IMTParser::get_autoVarDefinitionEnabled */ ,
    (void *) (INT_PTR) -1 /* IMTParser::put_autoVarDefinitionEnabled */ ,
    (void *) (INT_PTR) -1 /* IMTParser::get_syntax */ ,
    (void *) (INT_PTR) -1 /* IMTParser::putref_syntax */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineConst */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineFuncById */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineOpById */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineFuncsBySymbol */ ,
    (void *) (INT_PTR) -1 /* IMTParser::undefineOpsBySymbol */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getNbDefinedVars */ ,
    (void *) (INT_PTR) -1 /* IMTParser::getVar */ ,
    (void *) (INT_PTR) -1 /* IMTParser::defineFunc */ ,
    (void *) (INT_PTR) -1 /* IMTParser::evaluateCompiledBatchVB6 */
};


static const PRPC_STUB_FUNCTION IMTParser_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTParserStubVtbl =
{
    &IID_IMTParser,
    &IMTParser_ServerInfo,
    52,
    &IMTParser_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTDouble, ver. 0.0,
   GUID={0x287D18CE,0x1D30,0x4909,{0x80,0xD2,0xDF,0x45,0xDA,0x30,0x10,0xF4}} */

#pragma code_seg(".orpc")
static const unsigned short IMTDouble_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    2076,
    2118,
    2154,
    2190,
    2226,
    2262
    };

static const MIDL_STUBLESS_PROXY_INFO IMTDouble_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTDouble_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTDouble_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTDouble_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IMTDoubleProxyVtbl = 
{
    &IMTDouble_ProxyInfo,
    &IID_IMTDouble,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::create */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::get_value */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::put_value */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::get_name */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::setValue */ ,
    (void *) (INT_PTR) -1 /* IMTDouble::getValue */
};


static const PRPC_STUB_FUNCTION IMTDouble_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTDoubleStubVtbl =
{
    &IID_IMTDouble,
    &IMTDouble_ServerInfo,
    13,
    &IMTDouble_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTDate, ver. 0.0,
   GUID={0x3761F15D,0xE3AC,0x43D5,{0xAA,0x4A,0x33,0x3B,0x4F,0x71,0x36,0xD9}} */

#pragma code_seg(".orpc")
static const unsigned short IMTDate_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    2298,
    438,
    2334,
    2382,
    2430,
    2262,
    2466,
    2502,
    2538,
    2574
    };

static const MIDL_STUBLESS_PROXY_INFO IMTDate_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTDate_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTDate_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTDate_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IMTDateProxyVtbl = 
{
    &IMTDate_ProxyInfo,
    &IID_IMTDate,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTDate::create */ ,
    (void *) (INT_PTR) -1 /* IMTDate::parseDateTime */ ,
    (void *) (INT_PTR) -1 /* IMTDate::setDate */ ,
    (void *) (INT_PTR) -1 /* IMTDate::setTime */ ,
    (void *) (INT_PTR) -1 /* IMTDate::get_name */ ,
    (void *) (INT_PTR) -1 /* IMTDate::get_value */ ,
    (void *) (INT_PTR) -1 /* IMTDate::put_value */ ,
    (void *) (INT_PTR) -1 /* IMTDate::format */ ,
    (void *) (INT_PTR) -1 /* IMTDate::setValue */ ,
    (void *) (INT_PTR) -1 /* IMTDate::getValue */
};


static const PRPC_STUB_FUNCTION IMTDate_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTDateStubVtbl =
{
    &IID_IMTDate,
    &IMTDate_ServerInfo,
    17,
    &IMTDate_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTParserLocalizer, ver. 0.0,
   GUID={0x138338B4,0xB343,0x43C6,{0xB4,0xBB,0x2A,0x61,0x72,0x87,0x5E,0x47}} */

#pragma code_seg(".orpc")
static const unsigned short IMTParserLocalizer_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    2298,
    438,
    2610,
    144,
    2646,
    2682,
    2730,
    2772,
    2814,
    2862,
    2904,
    2946,
    2982,
    3018
    };

static const MIDL_STUBLESS_PROXY_INFO IMTParserLocalizer_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTParserLocalizer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTParserLocalizer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTParserLocalizer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(21) _IMTParserLocalizerProxyVtbl = 
{
    &IMTParserLocalizer_ProxyInfo,
    &IID_IMTParserLocalizer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::registerLibrary */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::setLocale */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getNbFuncs */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getNbOps */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getNbConsts */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getFuncInfo */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getOpInfo */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getConstInfo */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::formatExcep */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::registerAllLibraries */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getExcep */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::getLastExcep */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::get_locale */ ,
    (void *) (INT_PTR) -1 /* IMTParserLocalizer::put_locale */
};


static const PRPC_STUB_FUNCTION IMTParserLocalizer_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTParserLocalizerStubVtbl =
{
    &IID_IMTParserLocalizer,
    &IMTParserLocalizer_ServerInfo,
    21,
    &IMTParserLocalizer_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTExcepData, ver. 0.0,
   GUID={0xB75B4C3F,0xE77A,0x42DF,{0x8F,0x25,0xA3,0x68,0xDE,0xC3,0x73,0x09}} */

#pragma code_seg(".orpc")
static const unsigned short IMTExcepData_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3054,
    36,
    108,
    144,
    3090,
    3132,
    3174,
    3210
    };

static const MIDL_STUBLESS_PROXY_INFO IMTExcepData_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTExcepData_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTExcepData_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTExcepData_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IMTExcepDataProxyVtbl = 
{
    &IMTExcepData_ProxyInfo,
    &IID_IMTExcepData,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::setNativeData */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getNativeData */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getID */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getNbArgs */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getArgName */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getArgVal */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::getDescription */ ,
    (void *) (INT_PTR) -1 /* IMTExcepData::setDescription */
};


static const PRPC_STUB_FUNCTION IMTExcepData_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTExcepDataStubVtbl =
{
    &IID_IMTExcepData,
    &IMTExcepData_ServerInfo,
    15,
    &IMTExcepData_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMTDoubleVector, ver. 0.0,
   GUID={0x604EB4A2,0x9CB1,0x49CC,{0x8A,0xAD,0xFC,0x33,0xF4,0x8A,0x78,0xF4}} */

#pragma code_seg(".orpc")
static const unsigned short IMTDoubleVector_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3246,
    3282,
    3318,
    3354,
    3390
    };

static const MIDL_STUBLESS_PROXY_INFO IMTDoubleVector_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMTDoubleVector_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMTDoubleVector_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMTDoubleVector_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IMTDoubleVectorProxyVtbl = 
{
    &IMTDoubleVector_ProxyInfo,
    &IID_IMTDoubleVector,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMTDoubleVector::setValueVector */ ,
    (void *) (INT_PTR) -1 /* IMTDoubleVector::setValueVectorVB6 */ ,
    (void *) (INT_PTR) -1 /* IMTDoubleVector::create */ ,
    (void *) (INT_PTR) -1 /* IMTDoubleVector::registerListener */ ,
    (void *) (INT_PTR) -1 /* IMTDoubleVector::unregisterListener */
};


static const PRPC_STUB_FUNCTION IMTDoubleVector_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMTDoubleVectorStubVtbl =
{
    &IID_IMTDoubleVector,
    &IMTDoubleVector_ServerInfo,
    12,
    &IMTDoubleVector_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x6000169, /* MIDL Version 6.0.361 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _MTParserCOM_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMTParserProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTVariableProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTFunctionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTExcepDataProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTDateProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTDoubleVectorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTParserLocalizerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMTDoubleProxyVtbl,
    0
};

const CInterfaceStubVtbl * _MTParserCOM_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMTParserStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTVariableStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTFunctionStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTExcepDataStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTDateStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTDoubleVectorStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTParserLocalizerStubVtbl,
    ( CInterfaceStubVtbl *) &_IMTDoubleStubVtbl,
    0
};

PCInterfaceName const _MTParserCOM_InterfaceNamesList[] = 
{
    "IMTParser",
    "IMTVariable",
    "IMTFunction",
    "IMTExcepData",
    "IMTDate",
    "IMTDoubleVector",
    "IMTParserLocalizer",
    "IMTDouble",
    0
};

const IID *  _MTParserCOM_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _MTParserCOM_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _MTParserCOM, pIID, n)

int __stdcall _MTParserCOM_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _MTParserCOM, 8, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _MTParserCOM, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _MTParserCOM, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _MTParserCOM, 8, *pIndex )
    
}

const ExtendedProxyFileInfo MTParserCOM_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _MTParserCOM_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _MTParserCOM_StubVtblList,
    (const PCInterfaceName * ) & _MTParserCOM_InterfaceNamesList,
    (const IID ** ) & _MTParserCOM_BaseIIDList,
    & _MTParserCOM_IID_Lookup, 
    8,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

