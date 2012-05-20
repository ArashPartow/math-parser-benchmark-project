#include "MTExcepHelper.h"
#include "MTParserCOM.h"

MTExcepHelper::MTExcepHelper()
{
	clearLastExcep();
}

void MTExcepHelper::setLastExcep(const MTParserException &e)
{
	m_lastExcep.clear();
	
	for( unsigned int t=0; t<e.getNbDescs(); t++ )
	{		
		SLastException le;
		le.data = e.getException(t)->getData();
		le.desc = e.getDesc(t).c_str();
		
		m_lastExcep.push_back(le);
	}
}


void MTExcepHelper::getLastExcep(IMTExcepData *pExcep)
{
	pExcep->setNativeData((int)&m_lastExcep[0].data);	
	pExcep->setDescription(SysAllocString(MTSTRINGTOUNICODE(m_lastExcep[0].desc.c_str())));
	
	if( m_lastExcep.size() == 1 )
	{
		clearLastExcep();
	}
	else
	{
		// remove the first exception
		m_lastExcep.erase(m_lastExcep.begin());
	}
}

void MTExcepHelper::clearLastExcep()
{
	SLastException le;
	MTExcepData data(_T("ok"));
	le.data = data;
	le.desc = _T("All is fine and running");

	m_lastExcep.clear();		// clear all exceptions
	m_lastExcep.push_back(le);	// put a default exception
}

MTSTRING MTExcepHelper::getAllExceptionString(const MTParserException &e)
{
	MTSTRING msg;
	
	for( unsigned int t=0; t<e.getNbDescs(); t++ )
	{
		msg += e.getDesc(t).c_str();

		if( t != e.getNbDescs()-1 )
		{
			msg +=  _T("\r\n");
		}		
	}	

	return msg;
}
