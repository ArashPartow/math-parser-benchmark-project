#include "stdafx.h"
#include "Localization.h"
#include "Resource.h"

CString RToS(unsigned int id)
{
	CString msg;
	msg.LoadString(id);
	return msg;
}

MTSTRING getAllExceptionString(const MTParserException &e)
{
	MTSTRING msg;
	
	for( unsigned int t=0; t<e.getNbDescs(); t++ )
	{
		MTSTRING desc;
		
		// Take the localized exception description if available 
		try
		{
			desc = MTParserLocalizer::getInstance()->getExcep(e.getException(t)->getData());
		}
		catch( MTParserException )
		{
			// description not available...so take the default english message
			desc = e.getDesc(t).c_str();
		}
		msg += desc;

		if( t != e.getNbDescs()-1 )
		{
			msg +=  _T("\r\n");
		}		
	}	

	return msg;
}
