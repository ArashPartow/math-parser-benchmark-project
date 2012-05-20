/** @file MTUnicodeANSIDefs.h
	@brief Unicode and ANSI definitions.
	@author (c) 2008 Mathieu Jacques

	To let the choice to use Unicode strings or not,
	the proper types are defined here. By default the ANSI version is used.  
	To use the UNICODE version, just define the UNICODE and the _UNICODE symbols.	
*/

#ifndef _MTUNICODEANSIDEFS_INCLUDED
#define _MTUNICODEANSIDEFS_INCLUDED

#pragma warning( disable : 4786 )		// disable the debug info truncated warning

//******************************
// To enable the UNICODE string format use the following defines:
/*
#ifndef UNICODE
	#define UNICODE
#endif

#ifndef _UNICODE
	#define _UNICODE
#endif
*/

// you can also add these definitions in the project settings
//******************************


#include <tchar.h>
#include <string>



#ifdef UNICODE

	//! std widestring 
	#define MTSTRING		std::wstring
		
	//! Wide character 
	#define MTCHAR			wchar_t	
			
	//! Wide string to double 
	#define MTSTRTOD(/* const wchar_t* */ nptr, /* wchar_t** */ endptr)				\
				wcstod(nptr, endptr)	
			
	//! Long to wide string 
	#define MTLTOSTR(/* long */ value, /* wchar_t* */ string, /* int */ radix)		\
				_ltow(value, string, radix)	
			
	//! Tells whether a character is a digit (UNICODE version) 
	#define MTISDIGIT(/* wint_t */ c)												\
				iswdigit(c)																	

	//! Convert a Unicode string to an Unicode string...
	// "void": a Unicode is already Unicode and thus doesn't need to be converted
	#define UNICODETOMTSTRING(/* BSTR */ bstr)										\
				(bstr)	

	//! Convert a Unicode string to a Unicode string ...
	#define MTSTRINGTOUNICODE(/* MTCHAR* */ str)									\
				(str)

#else

	//! std ANSI string 
	#define MTSTRING		std::string	

	//! ANSI character
	#define MTCHAR			char				

	//! ANSI string to double 
	#define MTSTRTOD(/* const char* */ nptr, /* char** */ endptr)					\
				strtod(nptr, endptr)

	//! Long to ANSI string 
	#define MTLTOSTR(/* long */ value, /* char* */ string, /* int */ radix)			\
				_ltoa(value, string, radix)	

	//! Tells whether a character is a digit (ANSI version) 
	#define MTISDIGIT(/* int */ c)													\
				isdigit(c)	

	//! Convert a Unicode string to an ANSI string
	#define UNICODETOMTSTRING(/* wchar_t* */ bstr)									\
				MTUnicodeToANSI(bstr)	

	//! Convert an ANSI string to a Unicode string 
	#define MTSTRINGTOUNICODE(/* MTCHAR* */ str)									\
				(MTANSIToUnicode(str).c_str())
			
	

#endif

/** @brief Convert a Unicode string to an ANSI string

	@param	pStr	The Unicode string
	@return an ANSI string or an empty string if the Unicode string cannot be 
			converted correctly.
*/
std::string MTUnicodeToANSI(const wchar_t *pStr);

/** @brief Convert an ANSI string to an Unicode string

	@param	pStr	The ANSI string
	@return an Unicode string 
*/
std::wstring MTANSIToUnicode(const char *pStr);

#endif
