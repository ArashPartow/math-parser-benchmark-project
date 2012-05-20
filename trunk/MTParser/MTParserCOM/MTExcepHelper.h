#ifndef _MTEXCEPHELPER_INCLUDED
#define _MTEXCEPHELPER_INCLUDED

#include "../MTParserLib/MTParserException.h"

class MTExcepHelper
{
public:

	MTExcepHelper();

	// Set an exception
	void setLastExcep(const MTParserException &e);

	// Get one exception
	void getLastExcep(struct IMTExcepData *pExcep);

	// clears the exception structure
	void clearLastExcep();

	static MTSTRING getAllExceptionString(const MTParserException &e);

private:

	struct SLastException
	{
		MTExcepData data;
		MTSTRING desc;
	};
	
	std::vector<SLastException> m_lastExcep;			// last exception informations
	

};

#endif