#include "MTTools.h"
#include <math.h>
#include <windows.h>
#include <stdlib.h>		// for the MTLTOSTR macro that becomes _ltoa 

bool MTTools::findSubStr(const MTSTRING &str, const MTSTRING &subStr, unsigned int &pos)
{
	unsigned int strLength = str.size();
	unsigned int subStrLength = subStr.size();

	if( subStrLength > strLength )
	{
		return false;	
	}

	unsigned int end = strLength - subStrLength;

	for( unsigned int t=0; t <= end; t++ )
	{
		if( isStrBegin(str.c_str()+t, subStr.c_str(), strLength-t, subStrLength ) )
		{
			pos = t;
			return true;
		}

	}

	return false;
}

void MTTools::replaceSubStr(MTSTRING &str, const MTSTRING &subStr, const MTSTRING &newSubStr)
{
	unsigned int pos;
	if( findSubStr(str, subStr, pos) )
	{
		str.replace(pos, subStr.size(), newSubStr);
	}
}

bool MTTools::isStrBegin(const MTCHAR *str, const MTCHAR *beginStr, unsigned int strLength, unsigned int beginStrLength)
{	
	if( beginStrLength > strLength )
	{
		return false;	// cannot find a substring that is lengthier than the string itself!
	}
	
	for(unsigned int pos=0; pos < beginStrLength; pos++ )
	{
		if( str[pos] != beginStr[pos] )
		{
			return false;	// no match...!
		}
	}

	return true;	// match!		
}

void MTTools::removeSpaces(const MTSTRING &str, std::vector<unsigned int> &originalPos, MTSTRING &newStr)
{
	unsigned int length = str.size();
	newStr = _T("");
	newStr.reserve(length);
	originalPos.clear();
	originalPos.reserve(length);

	for( unsigned int t=0; t<length; t++ )
	{
		// add this character only if it is not a space character
		if( str[t] != ' ' )
		{			
			newStr += str[t];		
			originalPos.push_back(t);
		}
	}	
}

bool MTTools::findCharPos(const MTSTRING &str, unsigned int beginPos, const MTCHAR &c, unsigned int &pos)
{
	unsigned int length = str.size();

	for( unsigned int t=beginPos; t<length; t++ )
	{
		if( str[t] == c )
		{
			pos = t;
			return true;	// character found
		}
	}

	return false;		// character not found
}

void MTTools::parseString(const MTSTRING &str, const MTCHAR &c, std::vector<MTSTRING> &tokens)
{
	unsigned int length = str.size();
	unsigned int pos = 0;
	unsigned int separatorPos;
	
	tokens.clear();

	while( pos < length )
	{
		if( !findCharPos(str, pos, c, separatorPos) )
		{
			separatorPos = length;	// end of the string 
		}
		
		if( pos < separatorPos )
		{
			tokens.push_back(str.substr(pos, separatorPos-pos));
		}
		
		pos = separatorPos+1;
	}
}

// check if this word contains only numerical characters
bool MTTools::isOnlyNum(const MTSTRING &word, const MTCHAR &decimalPoint)
{	
	unsigned int length = word.size();
	bool decimal = false;	// indicate if a decimal point character has been encountered
							// at most it can only have one decimal point character
							// else, this is not a numerical only string

	for( unsigned int t=0; t<length; t++ )
	{
		// if this is not a numeric character and not the decimal point character
		if( !MTISDIGIT(word[t]) && word[t] != decimalPoint )
		{
			return false;	// alpha or special character
		}

		if( word[t] == decimalPoint )
		{
			if( decimal )
			{
				return false;	// a second decimal point character! 			
			}
			else
			{
				decimal = true;
			}

		}
			

	}

	return true;
}


double MTTools::generateNaN()
{
	unsigned long nan[2]={0xffffffff, 0x7fffffff};	// code representing a NaN
	return *( double* )nan;	
}

bool MTTools::registerCOMObject(const MTCHAR *file)
{
	HINSTANCE hLib = LoadLibrary(file);
    HRESULT (*lpDllEntryPoint)();

    if (hLib < (HINSTANCE)HINSTANCE_ERROR) 
    {
        return 0;
    }

    bool success = true;
    lpDllEntryPoint = (HRESULT (*)())GetProcAddress(hLib, "DllRegisterServer");
    if (lpDllEntryPoint != NULL)
    {
       HRESULT hr;
       hr = (*lpDllEntryPoint)();
       if (FAILED(hr))
       {
            success = false;
       }       
       
    } 
    else 
    {
        success = false;
    }
    
    FreeLibrary(hLib);
    return success;

}
	

bool MTTools::unregisterCOMObject(const MTCHAR *file)
{
	HINSTANCE hLib = LoadLibrary(file);
    HRESULT (*lpDllEntryPoint)();

    if (hLib < (HINSTANCE)HINSTANCE_ERROR) 
    {
        return 0;
    }


    bool success = 1;
    lpDllEntryPoint = (HRESULT (*)())GetProcAddress(hLib, "DllUnregisterServer");
    if (lpDllEntryPoint != NULL)
    {
       HRESULT hr;
       hr = (*lpDllEntryPoint)();
       if (FAILED(hr))
       {
            success = false;
       }              
    } 
    else 
    {
        success = false;
    }
 
    FreeLibrary(hLib);
    return success;

}

bool MTTools::registerTypeLib(const MTCHAR *file)
{
	ITypeLib *pTypeLib = NULL;

	if( FAILED(LoadTypeLib(MTSTRINGTOUNICODE(file),&pTypeLib) ))
	{
		return false;
	}	

	bool ret = true;
	if( FAILED(RegisterTypeLib(pTypeLib, (wchar_t*)MTSTRINGTOUNICODE(file), NULL) ))
	{
		ret = false;
	}

	pTypeLib->Release();
	pTypeLib = NULL;

	return ret;
}

bool MTTools::unregisterTypeLib(const MTCHAR *file)
{
	ITypeLib *pTypeLib = NULL;

	if( FAILED(LoadTypeLib(MTSTRINGTOUNICODE(file),&pTypeLib) ))
	{
		return false;
	}	

	TLIBATTR *pLibAttr;
	pTypeLib->GetLibAttr(&pLibAttr);
	
	bool ret = true;
	if( FAILED(UnRegisterTypeLib(pLibAttr->guid, pLibAttr->wMajorVerNum, pLibAttr->wMinorVerNum, pLibAttr->lcid, pLibAttr->syskind) ))
	{
		ret = false;
	}

	pTypeLib->Release();
	pTypeLib = NULL;

	return ret;
}


MTSTRING MTTools::doubleToS(double number, const MTCHAR &decimalPoint, unsigned int digits)
{
	// Custom double to string conversion since there is no
	// Unicode function to do this...
	
	MTSTRING str = longToS((int)number);
	str += decimalPoint;	

	unsigned int t;
	double fracPart = fabs(number) - fabs((double)((int)number));
	for( t=0; t<digits-1; t++ )	
	{
		fracPart *= 10.0;	
		if( (int)fracPart > 0 )
		{
			break;
		}	
		str += _T("0");	
	}

	fracPart *= pow(10.0, (int)(digits-t));
	str += longToS((int)fracPart);	

	return str;
}

MTSTRING MTTools::longToS(long val)
{
	MTCHAR str[20];
	return MTLTOSTR(val, str, 10);

}

