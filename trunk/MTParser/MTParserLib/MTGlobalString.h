/** @file MTGlobalString.h	
	@author (c) 2008 Mathieu Jacques
*/


#ifndef _MTGLOBALSTRING_INCLUDED
#define _MTGLOBALSTRING_INCLUDED

#include "MTUnicodeANSIDefs.h"
#include <windows.h>


/** @brief String allocated in global memory */
class MTGlobalString
{
public:

	/** @brief Create an empty string */
	MTGlobalString(){ m_buffer = NULL; m_size = 0;}
	
	/** @brief Copy an existing string */
	MTGlobalString(const MTGlobalString &obj)
	{
		m_buffer = NULL;		
		operator=(obj);
	}

	/** @brief Copy an existing string */
	MTGlobalString(const MTCHAR *str)
	{
		m_buffer = NULL;		
		allocStr(str);
	}

	/** @brief Copy an existing string */
	MTGlobalString& operator=(const MTGlobalString &obj)
	{
		allocStr(obj.c_str());
		return *this;
	}

	/** @brief Copy an existing string */
	MTGlobalString& operator=(const MTCHAR *str)
	{
		allocStr(str);
		return *this;
	}

	bool operator==(const MTCHAR *str)const
	{
		return lstrcmp(c_str(), str) == 0;
	}

	bool operator!=(const MTCHAR *str)const
	{
		return lstrcmp(c_str(), str) != 0;
	}

	/** @brief Get the string */
	const MTCHAR* c_str()const
	{
		if( m_buffer == NULL )
		{
			return _T("");
		}
		else
		{
			return (MTCHAR*)m_buffer;
		}
	}

	/** @brief Get the size of the string in characters */
	unsigned int size()const
	{
		return m_size;
	}

	~MTGlobalString(){ clean(); }


private:

	void clean()
	{
		if( m_buffer != NULL )
		{
			SysFreeString(m_buffer);
			m_buffer = NULL;
			m_size = 0;
		}
	}

	void allocStr(const MTCHAR *str)
	{
		clean();
		m_size = lstrlen(str);
		
		// allocate bytes for ANSI and Unicode as well
		m_buffer = SysAllocStringByteLen((const char*)str, sizeof(MTCHAR)*m_size);		
	}


private:

	BSTR m_buffer;			// the string memory buffer
	unsigned int m_size;	// the number of characters
};

#endif