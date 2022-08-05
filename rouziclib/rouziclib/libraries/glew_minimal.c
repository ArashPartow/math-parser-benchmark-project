// 2019, Michel Rouzic's stripped down rouziclib version

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

#include <stddef.h>  /* For size_t */

#if defined(__APPLE__)
#include <stdlib.h>
#include <string.h>
#include <AvailabilityMacros.h>

#ifdef MAC_OS_X_VERSION_10_3

#include <dlfcn.h>

void* NSGLGetProcAddress (const GLubyte *name)
{
  static void* image = NULL;
  void* addr;
  if (NULL == image)
  {
    image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);
  }
  if( !image ) return NULL;
  addr = dlsym(image, (const char*)name);
  if( addr ) return addr;
#ifdef GLEW_APPLE_GLX
  return dlGetProcAddress( name ); // try next for glx symbols
#else
  return NULL;
#endif
}
#else

#include <mach-o/dyld.h>

void* NSGLGetProcAddress (const GLubyte *name)
{
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
	 symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  if( symbol ) return NSAddressOfSymbol(symbol);
#ifdef GLEW_APPLE_GLX
  return dlGetProcAddress( name ); // try next for glx symbols
#else
  return NULL;
#endif
}
#endif /* MAC_OS_X_VERSION_10_3 */
#endif /* __APPLE__ */

/*
 * Define glewGetProcAddress.
 */
#if defined(_WIN32)
#  define glewGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#elif defined(__APPLE__) && !defined(GLEW_APPLE_GLX)
#  define glewGetProcAddress(name) NSGLGetProcAddress(name)
#else /* __linux */
#  define glewGetProcAddress(name) (*glXGetProcAddressARB)(name)
#endif

/*
 * Redefine GLEW_GET_VAR etc without const cast
 */

#undef GLEW_GET_VAR			// NEEDED_2
# define GLEW_GET_VAR(x) (x)			// NEEDED_2

#ifdef WGLEW_GET_VAR
# undef WGLEW_GET_VAR
# define WGLEW_GET_VAR(x) (x)
#endif /* WGLEW_GET_VAR */

#ifdef GLXEW_GET_VAR
# undef GLXEW_GET_VAR
# define GLXEW_GET_VAR(x) (x)
#endif /* GLXEW_GET_VAR */

#ifdef EGLEW_GET_VAR
# undef EGLEW_GET_VAR
# define EGLEW_GET_VAR(x) (x)
#endif /* EGLEW_GET_VAR */

/*
 * GLEW, just like OpenGL or GLU, does not rely on the standard C library.
 * These functions implement the functionality required in this file.
 */

static GLuint _glewStrLen (const GLubyte* s)
{
  GLuint i=0;
  if (s == NULL) return 0;
  while (s[i] != '\0') i++;
  return i;
}

static GLuint _glewStrCLen (const GLubyte* s, GLubyte c)			// NEEDED_2
{
  GLuint i=0;
  if (s == NULL) return 0;
  while (s[i] != '\0' && s[i] != c) i++;
  return i;
}

static GLuint _glewStrCopy(char *d, const char *s, char c)
{
  GLuint i=0;
  if (s == NULL) return 0;
  while (s[i] != '\0' && s[i] != c) { d[i] = s[i]; i++; }
  d[i] = '\0';
  return i;
}

#if !defined(GLEW_OSMESA)
#if !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
static GLboolean _glewStrSame (const GLubyte* a, const GLubyte* b, GLuint n)
{
  GLuint i=0;
  if(a == NULL || b == NULL)
    return (a == NULL && b == NULL && n == 0) ? GL_TRUE : GL_FALSE;
  while (i < n && a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) i++;
  return i == n ? GL_TRUE : GL_FALSE;
}
#endif
#endif

static GLboolean _glewStrSame1 (const GLubyte** a, GLuint* na, const GLubyte* b, GLuint nb)
{
  while (*na > 0 && (**a == ' ' || **a == '\n' || **a == '\r' || **a == '\t'))
  {
    (*a)++;
    (*na)--;
  }
  if(*na >= nb)
  {
    GLuint i=0;
    while (i < nb && (*a)+i != NULL && b+i != NULL && (*a)[i] == b[i]) i++;
    if(i == nb)
    {
      *a = *a + nb;
      *na = *na - nb;
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

static GLboolean _glewStrSame2 (const GLubyte** a, GLuint* na, const GLubyte* b, GLuint nb)
{
  if(*na >= nb)
  {
    GLuint i=0;
    while (i < nb && (*a)+i != NULL && b+i != NULL && (*a)[i] == b[i]) i++;
    if(i == nb)
    {
      *a = *a + nb;
      *na = *na - nb;
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

static GLboolean _glewStrSame3 (const GLubyte** a, GLuint* na, const GLubyte* b, GLuint nb)
{
  if(*na >= nb)
  {
    GLuint i=0;
    while (i < nb && (*a)+i != NULL && b+i != NULL && (*a)[i] == b[i]) i++;
    if (i == nb && (*na == nb || (*a)[i] == ' ' || (*a)[i] == '\n' || (*a)[i] == '\r' || (*a)[i] == '\t'))
    {
      *a = *a + nb;
      *na = *na - nb;
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

/*
 * Search for name in the extensions string. Use of strstr()
 * is not sufficient because extension names can be prefixes of
 * other extension names. Could use strtok() but the constant
 * string returned by glGetString might be in read-only memory.
 */
#if !defined(GLEW_OSMESA)
#if !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
static GLboolean _glewSearchExtension (const char* name, const GLubyte *start, const GLubyte *end)
{
  const GLubyte* p;
  GLuint len = _glewStrLen((const GLubyte*)name);
  p = start;
  while (p < end)
  {
    GLuint n = _glewStrCLen(p, ' ');
    if (len == n && _glewStrSame((const GLubyte*)name, p, n)) return GL_TRUE;
    p += n+1;
  }
  return GL_FALSE;
}
#endif
#endif

PFNGLCLEARTEXIMAGEPROC __glewClearTexImage = NULL;

GLboolean __GLEW_VERSION_1_1 = GL_FALSE;
GLboolean __GLEW_VERSION_1_2 = GL_FALSE;
GLboolean __GLEW_ARB_clear_texture = GL_FALSE;

static const char * _glewExtensionLookup[] = {
#ifdef GL_VERSION_1_2
  "GL_VERSION_1_2",
#endif
#ifdef GL_ARB_clear_texture			// NEEDED_1
  "GL_ARB_clear_texture",			// NEEDED_1
#endif			// NEEDED_1
  NULL
};

/* Detected in the extension string or strings */
static GLboolean  _glewExtensionString[801];			// NEEDED_2
/* Detected via extension string or experimental mode */
static GLboolean* _glewExtensionEnabled[] = {
#ifdef GL_VERSION_1_2
  &__GLEW_VERSION_1_2,
#endif
#ifdef GL_ARB_clear_texture
  &__GLEW_ARB_clear_texture,
#endif
  NULL
};
static GLboolean _glewInit_GL_VERSION_1_2 ();
static GLboolean _glewInit_GL_ARB_clear_texture ();			// NEEDED_1

#ifdef GL_VERSION_1_2

static GLboolean _glewInit_GL_VERSION_1_2 ()
{
  return CL_TRUE;
}

#endif /* GL_VERSION_1_2 */


#ifdef GL_ARB_clear_texture

static GLboolean _glewInit_GL_ARB_clear_texture ()			// NEEDED_1
{
  GLboolean r = GL_FALSE;

  r = ((glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)glewGetProcAddress((const GLubyte*)"glClearTexImage")) == NULL) || r;			// NEEDED_0

  return r;
}

#endif /* GL_ARB_clear_texture */



/* ------------------------------------------------------------------------- */

static int _glewExtensionCompare(const char *s1, const char *s2)
{
  /* http://www.chanduthedev.com/2012/07/strcmp-implementation-in-c.html */
  while (*s1 || *s2)
  {
      if (*s1 > *s2)
          return 1;
      if (*s1 < *s2)
          return -1;
      s1++;
      s2++;
  }
  return 0;
}

static ptrdiff_t _glewBsearchExtension(const char* name)
{
  ptrdiff_t lo = 0, hi = sizeof(_glewExtensionLookup) / sizeof(char*) - 2;

  while (lo <= hi)
  {
    ptrdiff_t mid = (lo + hi) / 2;
    const int cmp = _glewExtensionCompare(name, _glewExtensionLookup[mid]);
    if (cmp < 0) hi = mid - 1;
    else if (cmp > 0) lo = mid + 1;
    else return mid;
  }
  return -1;
}

static GLboolean *_glewGetExtensionString(const char *name)
{
  ptrdiff_t n = _glewBsearchExtension(name);
  if (n >= 0) return &_glewExtensionString[n];
  return NULL;
}

static GLboolean *_glewGetExtensionEnable(const char *name)
{
  ptrdiff_t n = _glewBsearchExtension(name);
  if (n >= 0) return _glewExtensionEnabled[n];
  return NULL;
}

static const char *_glewNextSpace(const char *i)
{
  const char *j = i;
  if (j)
    while (*j!=' ' && *j) ++j;
  return j;
}

static const char *_glewNextNonSpace(const char *i)
{
  const char *j = i;
  if (j)
    while (*j==' ') ++j;
  return j;
}

GLboolean GLEWAPIENTRY glewGetExtension (const char* name)
{
  GLboolean *enable = _glewGetExtensionString(name);
  if (enable)
    return *enable;
  return GL_FALSE;
}

/* ------------------------------------------------------------------------- */

typedef const GLubyte* (GLAPIENTRY * PFNGLGETSTRINGPROC) (GLenum name);
typedef void (GLAPIENTRY * PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);

static GLenum GLEWAPIENTRY glewContextInit ()			// NEEDED_1
{
  PFNGLGETSTRINGPROC getString;
  const GLubyte* s;
  GLuint dot;
  GLint major, minor;
  size_t n;

  #ifdef _WIN32
  getString = glGetString;
  #else
  getString = (PFNGLGETSTRINGPROC) glewGetProcAddress((const GLubyte*)"glGetString");
  if (!getString)
    return GLEW_ERROR_NO_GL_VERSION;
  #endif

  /* query opengl version */
  s = getString(GL_VERSION);
  dot = _glewStrCLen(s, '.');
  if (dot == 0)
    return GLEW_ERROR_NO_GL_VERSION;

  major = s[dot-1]-'0';
  minor = s[dot+1]-'0';

  if (minor < 0 || minor > 9)
    minor = 0;
  if (major<0 || major>9)
    return GLEW_ERROR_NO_GL_VERSION;

  if (major == 1 && minor == 0)
  {
    return GLEW_ERROR_GL_VERSION_10_ONLY;
  }
  else
  {
    GLEW_VERSION_1_2   = ( major >= 2 )                || ( major == 1 && minor >= 2 ) ? GL_TRUE : GL_FALSE;
    GLEW_VERSION_1_1   = GLEW_VERSION_1_2   == GL_TRUE || ( major == 1 && minor >= 1 ) ? GL_TRUE : GL_FALSE;
  }

  for (n = 0; n < sizeof(_glewExtensionString) / sizeof(_glewExtensionString[0]); ++n)
    _glewExtensionString[n] = GL_FALSE;

  if (1)
  {
    const char *extensions;
    const char *end;
    const char *i;
    const char *j;
    char ext[128];
    GLboolean *enable;

    extensions = (const char *) getString(GL_EXTENSIONS);

    if (extensions)
    {
      end = extensions + _glewStrLen((const GLubyte *) extensions);
      for (i=extensions; i<end; i = j + 1)
      {
        i = _glewNextNonSpace(i);
        j = _glewNextSpace(i);

        /* Copy extension into NUL terminated string */
        if (j-i >= (ptrdiff_t) sizeof(ext))
          continue;
        _glewStrCopy(ext, i, ' ');

        /* Based on extension string(s), glewGetExtension purposes */
        enable = _glewGetExtensionString(ext);
        if (enable)
          *enable = GL_TRUE;

        /* Based on extension string(s), experimental mode, glewIsSupported purposes */
        enable = _glewGetExtensionEnable(ext);
        if (enable)
          *enable = GL_TRUE;
      }
    }
  }
#ifdef GL_VERSION_1_2
  if (glewExperimental || GLEW_VERSION_1_2) GLEW_VERSION_1_2 = !_glewInit_GL_VERSION_1_2();
#endif /* GL_VERSION_1_2 */
#ifdef GL_ARB_clear_texture
  if (glewExperimental || GLEW_ARB_clear_texture) GLEW_ARB_clear_texture = !_glewInit_GL_ARB_clear_texture();
#endif /* GL_ARB_clear_texture */

  return GLEW_OK;
}



/* ------------------------------------------------------------------------ */

const GLubyte * GLEWAPIENTRY glewGetErrorString (GLenum error)
{
  static const GLubyte* _glewErrorString[] =
  {
    (const GLubyte*)"No error",
    (const GLubyte*)"Missing GL version",
    (const GLubyte*)"GL 1.1 and up are not supported",
    (const GLubyte*)"GLX 1.2 and up are not supported",
    (const GLubyte*)"Unknown error"
  };
  const size_t max_error = sizeof(_glewErrorString)/sizeof(*_glewErrorString) - 1;
  return _glewErrorString[(size_t)error > max_error ? max_error : (size_t)error];
}

const GLubyte * GLEWAPIENTRY glewGetString (GLenum name)
{
  static const GLubyte* _glewString[] =
  {
    (const GLubyte*)NULL,
    (const GLubyte*)"2.1.0",
    (const GLubyte*)"2",
    (const GLubyte*)"1",
    (const GLubyte*)"0"
  };
  const size_t max_string = sizeof(_glewString)/sizeof(*_glewString) - 1;
  return _glewString[(size_t)name > max_string ? 0 : (size_t)name];
}

/* ------------------------------------------------------------------------ */

GLboolean glewExperimental = GL_FALSE;

GLenum GLEWAPIENTRY glewInit (void)			// NEEDED_0
{
  GLenum r;

  r = glewContextInit();

  return r;
}

#if defined(_WIN32) && defined(GLEW_BUILD) && defined(__GNUC__)
/* GCC requires a DLL entry point even without any standard library included. */
/* Types extracted from windows.h to avoid polluting the rest of the file. */
int __stdcall DllMainCRTStartup(void* instance, unsigned reason, void* reserved)
{
  (void) instance;
  (void) reason;
  (void) reserved;
  return 1;
}
#endif
GLboolean GLEWAPIENTRY glewIsSupported (const char* name)
{
  const GLubyte* pos = (const GLubyte*)name;
  GLuint len = _glewStrLen(pos);
  GLboolean ret = GL_TRUE;
  while (ret && len > 0)
  {
    if (_glewStrSame1(&pos, &len, (const GLubyte*)"GL_", 3))
    {
      if (_glewStrSame2(&pos, &len, (const GLubyte*)"VERSION_", 8))
      {
#ifdef GL_VERSION_1_2
        if (_glewStrSame3(&pos, &len, (const GLubyte*)"1_2", 3))
        {
          ret = GLEW_VERSION_1_2;
          continue;
        }
#endif
#ifdef GL_ARB_clear_texture
        if (_glewStrSame3(&pos, &len, (const GLubyte*)"clear_texture", 13))
        {
          ret = GLEW_ARB_clear_texture;
          continue;
        }
#endif
      }
    }
    ret = (len == 0);
  }
  return ret;
}
