// 2019, Michel Rouzic's stripped down rouziclib version

/* Notes of needed symbols by the rest of rouziclib:
GL_CLAMP_TO_EDGE	// GL_VERSION_1_2
GL_QUADS		// GL_VERSION_1_1
GL_RGBA			// GL_VERSION_1_1
GL_RGBA8		// GL_VERSION_1_1
GL_TEXTURE_2D		// GL_VERSION_1_1
GL_TEXTURE_BASE_LEVEL	// GL_VERSION_1_2
GL_TEXTURE_MAG_FILTER	// GL_VERSION_1_1
GL_TEXTURE_MAX_LEVEL	// GL_VERSION_1_2
GL_TEXTURE_MIN_FILTER	// GL_VERSION_1_1
GL_TEXTURE_WRAP_S	// GL_VERSION_1_1
GL_TEXTURE_WRAP_T	// GL_VERSION_1_1
GL_UNSIGNED_BYTE	// GL_VERSION_1_1
GLenum			// GL_VERSION_1_1
glBegin			// GL_VERSION_1_1
glBindTexture		// GL_VERSION_1_1
glClearTexImage		// GL_ARB_clear_texture
glEnable		// GL_VERSION_1_1
glEnd			// GL_VERSION_1_1
glFinish		// GL_VERSION_1_1
glFlush			// GL_VERSION_1_1
glGenTextures		// GL_VERSION_1_1
glLoadIdentity		// GL_VERSION_1_1
glTexCoord2f		// GL_VERSION_1_1
glTexImage2D		// GL_VERSION_1_1
glTexParameteri		// GL_VERSION_1_1
glVertex2f		// GL_VERSION_1_1
glViewport		// GL_VERSION_1_1
glXGetCurrentContext()	// not in GLEW
glXGetCurrentDisplay()	// GLX_VERSION_1_2 (set only, not defined)
glewExperimental
glewInit
wglGetCurrentContext	// not in GLEW
wglGetCurrentDC		// not in GLEW
*/

/*
** The OpenGL Extension Wrangler Library
** Copyright (C) 2008-2017, Nigel Stewart <nigels[]users sourceforge net>
** Copyright (C) 2002-2008, Milan Ikits <milan ikits[]ieee org>
** Copyright (C) 2002-2008, Marcelo E. Magallon <mmagallo[]debian org>
** Copyright (C) 2002, Lev Povalahev
** All rights reserved.
** 
** Redistribution and use in source and binary forms, with or without 
** modification, are permitted provided that the following conditions are met:
** 
** * Redistributions of source code must retain the above copyright notice, 
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice, 
**   this list of conditions and the following disclaimer in the documentation 
**   and/or other materials provided with the distribution.
** * The name of the author may be used to endorse or promote products 
**   derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
** THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __glew_h__
#define __glew_h__
#define __GLEW_H__

#if defined(__gl_h_) || defined(__GL_H__) || defined(_GL_H) || defined(__X_GL_H)
#error gl.h included before glew.h
#endif
#if defined(__gl2_h_)
#error gl2.h included before glew.h
#endif
#if defined(__gltypes_h_)
#error gltypes.h included before glew.h
#endif
#if defined(__REGAL_H__)
#error Regal.h included before glew.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error glext.h included before glew.h
#endif
#if defined(__gl_ATI_h_)
#error glATI.h included before glew.h
#endif

#define __gl_h_
#define __gl2_h_
#define __GL_H__
#define _GL_H
#define __gltypes_h_
#define __REGAL_H__
#define __X_GL_H
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_

#if defined(_WIN32)

/*
 * GLEW does not include <windows.h> to avoid name space pollution.
 * GL needs GLAPI and GLAPIENTRY, GLU needs APIENTRY, CALLBACK, and wchar_t
 * defined properly.
 */
/* <windef.h> and <gl.h>*/			// NEEDED_1
#ifdef APIENTRY
#  ifndef GLAPIENTRY
#    define GLAPIENTRY APIENTRY
#  endif
#  ifndef GLEWAPIENTRY
#    define GLEWAPIENTRY APIENTRY
#  endif
#else
#define GLEW_APIENTRY_DEFINED
#  if defined(__MINGW32__) || defined(__CYGWIN__) || (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#    define APIENTRY __stdcall
#    ifndef GLAPIENTRY
#      define GLAPIENTRY __stdcall
#    endif
#    ifndef GLEWAPIENTRY
#      define GLEWAPIENTRY __stdcall
#    endif
#  else
#    define APIENTRY
#  endif
#endif
#ifndef GLAPI			// NEEDED_1
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define GLAPI extern
#  endif
#endif
/* <winnt.h> */
#ifndef CALLBACK
#define GLEW_CALLBACK_DEFINED
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define CALLBACK __attribute__ ((__stdcall__))
#  elif (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#    define CALLBACK __stdcall
#  else
#    define CALLBACK
#  endif
#endif
/* <wingdi.h> and <winnt.h> */
#ifndef WINGDIAPI
#define GLEW_WINGDIAPI_DEFINED
#define WINGDIAPI __declspec(dllimport)
#endif
/* <ctype.h> */
#if (defined(_MSC_VER) || defined(__BORLANDC__)) && !defined(_WCHAR_T_DEFINED)
typedef unsigned short wchar_t;
#  define _WCHAR_T_DEFINED
#endif
/* <stddef.h> */
#if !defined(_W64)
#  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && defined(_MSC_VER) && _MSC_VER >= 1300
#    define _W64 __w64
#  else
#    define _W64
#  endif
#endif
#if !defined(_PTRDIFF_T_DEFINED) && !defined(_PTRDIFF_T_) && !defined(__MINGW64__)
#  ifdef _WIN64
typedef __int64 ptrdiff_t;
#  else
typedef _W64 int ptrdiff_t;
#  endif
#  define _PTRDIFF_T_DEFINED
#  define _PTRDIFF_T_
#endif

#ifndef GLAPI
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define GLAPI extern
#  else
#    define GLAPI WINGDIAPI
#  endif
#endif

/*
 * GLEW_STATIC is defined for static library.
 * GLEW_BUILD  is defined for building the DLL library.
 */

#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  ifdef GLEW_BUILD
#    define GLEWAPI extern __declspec(dllexport)
#  else
#    define GLEWAPI extern __declspec(dllimport)
#  endif
#endif

#else /* _UNIX */

/*
 * Needed for ptrdiff_t in turn needed by VBO.  This is defined by ISO
 * C.  On my system, this amounts to _3 lines_ of included code, all of
 * them pretty much harmless.  If you know of a way of detecting 32 vs
 * 64 _targets_ at compile time you are free to replace this with
 * something that's portable.  For now, _this_ is the portable solution.
 * (mem, 2004-01-04)
 */

#include <stddef.h>

/* SGI MIPSPro doesn't like stdint.h in C++ mode          */
/* ID: 3376260 Solaris 9 has inttypes.h, but not stdint.h */

#if (defined(__sgi) || defined(__sun)) && !defined(__GNUC__)
#include <inttypes.h>
#else
#include <stdint.h>
#endif

#define GLEW_APIENTRY_DEFINED
#define APIENTRY

/*
 * GLEW_STATIC is defined for static library.
 */

#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  if defined(__GNUC__) && __GNUC__>=4
#   define GLEWAPI extern __attribute__ ((visibility("default")))
#  elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#   define GLEWAPI extern __global
#  else
#   define GLEWAPI extern
#  endif
#endif

/* <glu.h> */
#ifndef GLAPI
#define GLAPI extern
#endif

#endif /* _WIN32 */

#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif

#ifndef GLEWAPIENTRY
#define GLEWAPIENTRY
#endif

#define GLEW_VAR_EXPORT GLEWAPI
#define GLEW_FUN_EXPORT GLEWAPI

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------- GL_VERSION_1_1 ---------------------------- */

#ifndef GL_VERSION_1_1
#define GL_VERSION_1_1 1

typedef unsigned int GLenum;			// NEEDED_0
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;			// NEEDED_2
typedef int GLint;			// NEEDED_2
typedef int GLsizei;
typedef unsigned char GLboolean;			// NEEDED_1
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;			// NEEDED_2
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
#if defined(_MSC_VER) && _MSC_VER < 1400
typedef __int64 GLint64EXT;
typedef unsigned __int64 GLuint64EXT;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
typedef signed long long GLint64EXT;
typedef unsigned long long GLuint64EXT;
#else
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#include <inttypes.h>
#  endif
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
#endif
typedef GLint64EXT  GLint64;
typedef GLuint64EXT GLuint64;
typedef struct __GLsync *GLsync;

typedef char GLchar;

#define GL_FALSE 0			// NEEDED_1
#define GL_TRUE 1			// NEEDED_?
#define GL_QUADS 0x0007			// NEEDED_0
#define GL_TEXTURE_2D 0x0DE1			// NEEDED_0
#define GL_UNSIGNED_BYTE 0x1401			// NEEDED_0
#define GL_RGBA 0x1908			// NEEDED_0
#define GL_RENDERER 0x1F01		// NEEDED_?
#define GL_VERSION 0x1F02		// NEEDED_?
#define GL_EXTENSIONS 0x1F03		// NEEDED_?
#define GL_NEAREST 0x2600		// NEEDED_?
#define GL_TEXTURE_MAG_FILTER 0x2800			// NEEDED_0
#define GL_TEXTURE_MIN_FILTER 0x2801			// NEEDED_0
#define GL_TEXTURE_WRAP_S 0x2802			// NEEDED_0
#define GL_TEXTURE_WRAP_T 0x2803			// NEEDED_0
#define GL_RGBA8 0x8058			// NEEDED_0

GLAPI void GLAPIENTRY glBegin (GLenum mode);			// NEEDED_0
GLAPI void GLAPIENTRY glBindTexture (GLenum target, GLuint texture);			// NEEDED_0
GLAPI void GLAPIENTRY glEnable (GLenum cap);			// NEEDED_0
GLAPI void GLAPIENTRY glEnd (void);			// NEEDED_0
GLAPI void GLAPIENTRY glFinish (void);			// NEEDED_0
GLAPI void GLAPIENTRY glFlush (void);			// NEEDED_0
GLAPI void GLAPIENTRY glGenTextures (GLsizei n, GLuint *textures);			// NEEDED_0
GLAPI const GLubyte * GLAPIENTRY glGetString (GLenum name);			// NEEDED_2
GLAPI void GLAPIENTRY glLoadIdentity (void);			// NEEDED_0
GLAPI void GLAPIENTRY glTexCoord2f (GLfloat s, GLfloat t);			// NEEDED_0
GLAPI void GLAPIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);			// NEEDED_0
GLAPI void GLAPIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);			// NEEDED_0
GLAPI void GLAPIENTRY glVertex2f (GLfloat x, GLfloat y);			// NEEDED_0
GLAPI void GLAPIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);			// NEEDED_0

#define GLEW_VERSION_1_1 GLEW_GET_VAR(__GLEW_VERSION_1_1)

#endif /* GL_VERSION_1_1 */

/* ----------------------------- GL_VERSION_1_2 ---------------------------- */

#ifndef GL_VERSION_1_2
#define GL_VERSION_1_2 1

#define GL_CLAMP_TO_EDGE 0x812F			// NEEDED_0
#define GL_TEXTURE_BASE_LEVEL 0x813C			// NEEDED_0
#define GL_TEXTURE_MAX_LEVEL 0x813D			// NEEDED_0

#define GLEW_VERSION_1_2 GLEW_GET_VAR(__GLEW_VERSION_1_2)

#endif /* GL_VERSION_1_2 */

/* -------------------------- GL_ARB_clear_texture ------------------------- */

#ifndef GL_ARB_clear_texture
#define GL_ARB_clear_texture 1

#define GL_CLEAR_TEXTURE 0x9365

typedef void (GLAPIENTRY * PFNGLCLEARTEXIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data);

#define glClearTexImage GLEW_GET_FUN(__glewClearTexImage)			// NEEDED_0

#define GLEW_ARB_clear_texture GLEW_GET_VAR(__GLEW_ARB_clear_texture)			// NEEDED_1

#endif /* GL_ARB_clear_texture */

/* ------------------------------------------------------------------------- */


GLEW_FUN_EXPORT PFNGLCLEARTEXIMAGEPROC __glewClearTexImage;
GLEW_VAR_EXPORT GLboolean __GLEW_ARB_clear_texture;			// NEEDED_2
/* ------------------------------------------------------------------------- */

/* error codes */
#define GLEW_OK 0
#define GLEW_NO_ERROR 0
#define GLEW_ERROR_NO_GL_VERSION 1  /* missing GL version */			// NEEDED_2
#define GLEW_ERROR_GL_VERSION_10_ONLY 2  /* Need at least OpenGL 1.1 */
#define GLEW_ERROR_GLX_VERSION_11_ONLY 3  /* Need at least GLX 1.2 */
#define GLEW_ERROR_NO_GLX_DISPLAY 4  /* Need GLX display for GLX support */

/* string codes */
#define GLEW_VERSION 1
#define GLEW_VERSION_MAJOR 2
#define GLEW_VERSION_MINOR 3
#define GLEW_VERSION_MICRO 4

/* ------------------------------------------------------------------------- */

/* GLEW version info */

/*
VERSION 2.1.0
VERSION_MAJOR 2
VERSION_MINOR 1
VERSION_MICRO 0
*/

/* API */
GLEWAPI GLenum GLEWAPIENTRY glewInit (void);			// NEEDED_0
GLEWAPI GLboolean GLEWAPIENTRY glewIsSupported (const char *name);
#define glewIsExtensionSupported(x) glewIsSupported(x)

#ifndef GLEW_GET_VAR			// NEEDED_2
#define GLEW_GET_VAR(x) (*(const GLboolean*)&x)			// NEEDED_2
#endif			// NEEDED_2

#ifndef GLEW_GET_FUN			// NEEDED_0
#define GLEW_GET_FUN(x) x			// NEEDED_0
#endif			// NEEDED_0

GLEWAPI GLboolean glewExperimental;			// NEEDED_0
GLEWAPI GLboolean GLEWAPIENTRY glewGetExtension (const char *name);
GLEWAPI const GLubyte * GLEWAPIENTRY glewGetErrorString (GLenum error);
GLEWAPI const GLubyte * GLEWAPIENTRY glewGetString (GLenum name);

#ifdef __cplusplus
}
#endif

#ifdef GLEW_APIENTRY_DEFINED
#undef GLEW_APIENTRY_DEFINED
#undef APIENTRY
#endif

#ifdef GLEW_CALLBACK_DEFINED
#undef GLEW_CALLBACK_DEFINED
#undef CALLBACK
#endif

#ifdef GLEW_WINGDIAPI_DEFINED
#undef GLEW_WINGDIAPI_DEFINED
#undef WINGDIAPI
#endif

#undef GLAPI
/* #undef GLEWAPI */

#endif /* __glew_h__ */
