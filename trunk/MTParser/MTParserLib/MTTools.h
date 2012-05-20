/** @file MTTools.h
	@brief Common internal tools 	
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTTOOLS_INCLUDED
#define _MTTOOLS_INCLUDED

#include "MTUnicodeANSIDefs.h"
#include <vector>

namespace MTTools
{

/** @brief Try to find this sub-string

	@param	str		Source string
	@param	subStr	The substring to find
	@param	pos		[out] The position where the substring has been found
	@return True if the string contains this subString
*/
bool findSubStr(const MTSTRING &str, const MTSTRING &subStr, unsigned int &pos);

/** @brief Replace a substring by a new string

	If the substring is not found then the str param is not modified and
	no error is returned.

	@param	str			[in, out] Source string
	@param	subStr		The substring to find
	@param	newSubStr	The new substring	
*/
void replaceSubStr(MTSTRING &str, const MTSTRING &subStr, const MTSTRING &newSubStr);

/** @brief Check whether a string is prefixed by another string 

	@param	str				Source string
	@param	beginStr		The prefix string
	@param	strLength		Source string length.  For performance reason, it is
							better to pass this parameter to the function.  
	@param beginStrLength	Prefix string length.  For performance reason, it is
							better to pass this parameter to the function.  
	@return True if the string begins with the beginStr string
*/
bool isStrBegin(const MTCHAR *str, const MTCHAR *beginStr, unsigned int strLength, unsigned int beginStrLength);
	
/** @brief Remove all space characters from the string

	@param	str				Source string
	@param	originalPos		[out] The original position for each character in the
							new string.
	@param	newStr			[out] The string without spaces	
*/
void removeSpaces(const MTSTRING &str, std::vector<unsigned int> &originalPos, MTSTRING &newStr);

/** @brief Find the position of a character in the string

	@param	str				Source string
	@param	beginPos		The position where the search begins 
	@param	c				The character to find
	@param	pos				[out] The position of the character

	@return true if the character has been found, else false
*/
bool findCharPos(const MTSTRING &str, unsigned int beginPos, const MTCHAR &c, unsigned int &pos);

/* @brief Parse a string using a separator character

	Find all tokens separated by the specified character.

	@param	str				Source string
	@param	c				Separator character
	@param	tokens			[out] A vector containing all tokens	
*/
void parseString(const MTSTRING &str, const MTCHAR &c, std::vector<MTSTRING> &tokens);

/** @brief Check whether a string contains only numerical characters

	Numerical characters are: [0-9] and the decimal point character

	@param	word	A string
	@return	True if this word contains only numerical characters
*/ 
bool isOnlyNum(const MTSTRING &word, const MTCHAR &decimalPoint);

/** @brief Convert a double number to a string

  The number is formated using the decimal point character
  specified by the syntax.

  @param	number			The number to be formatted 
  @param	decimalPoint	The decimal point character
  @param	digits			number of significant digits

  @return A string representing the number 
*/
MTSTRING doubleToS(double number, const MTCHAR &decimalPoint, unsigned int digits = 6);


/** @brief Convert a number to a string

  @param	val		The interger value

  @return A string representing the number
*/
MTSTRING longToS(long val);


/** @brief Generate a NaN value
	@return A NaN value
*/
double generateNaN();

/** @brief Register a COM object 

	Plugins are COM objects.  A COM object must be registered before it could be used.

	@param	file	The path of the COM object file
	@return	True if the object has been sucessfully registered
*/
bool registerCOMObject(const MTCHAR *file);

/** @brief Unregister a COM object

	This cleans the Windows registry

	@param	file	The path of the COM object file
	@return True if the object has been sucessfully unregistered
*/
bool unregisterCOMObject(const MTCHAR *file);	

/** @brief Register a type library

	Add the registry entries.

	@param	file	The library path or filename
	@return true if the library has been sucessfully registered
*/
bool registerTypeLib(const MTCHAR *file);

/** @brief Unregister a type library

	Remove the registry entries.

	@param	file	The library path or filename
	@return true if the library has been sucessfully unregistered

*/
bool unregisterTypeLib(const MTCHAR *file);

//! NaN value
const double NaN = MTTools::generateNaN();


};	// namespace MTTools

#endif