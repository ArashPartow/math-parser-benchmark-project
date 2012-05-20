/** @file MTParserExcepStrEng.h
	@brief Default english exception message formatter
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSEREXCEPSTRENG_INCLUDED
#define _MTPARSEREXCEPSTRENG_INCLUDED

#pragma warning( disable : 4786 )		// disable the debug info truncated warning

#include "MTParserException.h"

/** @brief English exception message formatter

	Format exceptions to readable english
	messages. 
*/
class MTParserExcepStrEng
{
public:

	/** @brief Format an exception
	@param data	The definition exception date
	@return An english message describing the exception
	*/
	static MTSTRING format(const MTExcepData &data);	

	/** @brief Helper method to format an exception string

		Replace arguments by their values.  Arguments are:
		%pos, %itemName, %conflictItemName, %param1, %param2

		@param	data	The exception
		@param	msg		The message string with arguments

	*/
	static MTSTRING format(const MTExcepData &data, const MTCHAR *msg);
	
private:

	MTParserExcepStrEng();
	void addExcep(const MTCHAR *id, const MTCHAR *msg);

	MTSTRING internalFormat(const MTExcepData &data);		

private:

	static MTParserExcepStrEng m_instance;
	
	struct SExcepInfo
	{
		MTSTRING id;
		MTSTRING msg;
	};

	std::vector<SExcepInfo> m_exceps;	

};


#endif