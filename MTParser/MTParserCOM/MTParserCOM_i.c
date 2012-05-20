

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMTVariable,0xAC930F10,0x590E,0x5928,0xBE,0x23,0x12,0xC6,0x94,0xD5,0xB0,0x35);


MIDL_DEFINE_GUID(IID, IID_IMTFunction,0xED930F11,0x520E,0x5926,0xBE,0x23,0x12,0xC6,0x94,0xD5,0xB0,0x35);


MIDL_DEFINE_GUID(IID, IID_IMTParser,0xAB830D10,0x490E,0x4228,0xAE,0x23,0x01,0xC7,0x94,0xE5,0xC0,0x36);


MIDL_DEFINE_GUID(IID, IID_IMTDouble,0x287D18CE,0x1D30,0x4909,0x80,0xD2,0xDF,0x45,0xDA,0x30,0x10,0xF4);


MIDL_DEFINE_GUID(IID, IID_IMTDate,0x3761F15D,0xE3AC,0x43D5,0xAA,0x4A,0x33,0x3B,0x4F,0x71,0x36,0xD9);


MIDL_DEFINE_GUID(IID, IID_IMTParserLocalizer,0x138338B4,0xB343,0x43C6,0xB4,0xBB,0x2A,0x61,0x72,0x87,0x5E,0x47);


MIDL_DEFINE_GUID(IID, IID_IMTExcepData,0xB75B4C3F,0xE77A,0x42DF,0x8F,0x25,0xA3,0x68,0xDE,0xC3,0x73,0x09);


MIDL_DEFINE_GUID(IID, IID_IMTDoubleVector,0x604EB4A2,0x9CB1,0x49CC,0x8A,0xAD,0xFC,0x33,0xF4,0x8A,0x78,0xF4);


MIDL_DEFINE_GUID(IID, LIBID_MTPARSERCOMLib,0x3A10DDB0,0x09C0,0x4C59,0xAF,0xC5,0x71,0xC3,0xEF,0x08,0x2D,0xC3);


MIDL_DEFINE_GUID(CLSID, CLSID_MTParser,0x8C49E58A,0xFFEA,0x48F0,0xA4,0x2D,0x68,0xD2,0xFB,0xE1,0x46,0x03);


MIDL_DEFINE_GUID(CLSID, CLSID_MTDouble,0x0146FD58,0x5279,0x4F3F,0xA7,0x0B,0x77,0x84,0x5A,0x2E,0x7B,0x75);


MIDL_DEFINE_GUID(CLSID, CLSID_MTDate,0x39726397,0xB802,0x4AB7,0x90,0xB4,0x16,0x57,0x20,0x07,0x02,0x7F);


MIDL_DEFINE_GUID(CLSID, CLSID_MTParserLocalizer,0x766FBDFE,0x9EBB,0x43BD,0xBA,0x47,0x46,0x67,0xB0,0x0D,0xD3,0xF9);


MIDL_DEFINE_GUID(CLSID, CLSID_MTExcepData,0x2B8F32EE,0x6861,0x442E,0x90,0x71,0x31,0x2E,0x93,0xCC,0x4C,0xF0);


MIDL_DEFINE_GUID(CLSID, CLSID_MTDoubleVector,0x16E097BF,0x2BC4,0x4377,0x9D,0xA1,0xE2,0x80,0x6A,0xCA,0x81,0xC4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

