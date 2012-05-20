#include "MTUnicodeANSIDefs.h"
#include <stdlib.h>		// for the wcstombs function

std::string MTUnicodeToANSI(const wchar_t *pStr)
{
	std::string str;

	if( pStr == NULL )
	{
		return str;
	}
	
	// Get the required buffer size
	unsigned int size = wcstombs(NULL, pStr, 0);
	char *pBuffer = new char[size+1];
	if( pBuffer == NULL )
	{
		// out of memory
		return str;
	}
	pBuffer[size] = 0;
	
	if( wcstombs(pBuffer, pStr, size) != (size_t)-1 )
	{
		str = pBuffer;
	}
	delete []pBuffer;
	return str;
}

std::wstring MTANSIToUnicode(const char *pStr)
{
	std::wstring str;
	
	// Get the required buffer size
	unsigned int size = mbstowcs(NULL, pStr, 0);
	wchar_t *pBuffer = new wchar_t[size+1];
	if( pBuffer == NULL )
	{
		// out of memory
		return str;
	}
	pBuffer[size] = 0;
	
	if( mbstowcs(pBuffer, pStr, size) != (size_t)-1 )
	{
		str = pBuffer;
	}
	delete []pBuffer;
	return str;

}