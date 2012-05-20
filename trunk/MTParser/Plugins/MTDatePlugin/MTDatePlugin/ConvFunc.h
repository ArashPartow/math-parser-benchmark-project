#ifndef _CONVFUNC_INCLUDED
#define _CONVFUNC_INCLUDED

#include "..\..\..\MTParserLib\MTParserPrivate.h"
#include "..\..\..\MTParserLib\MTParserException.h"


class DateConvFunc : public MTConvFunctionI
{
public:

	
	virtual const MTCHAR* getSymbol(){return _T("datevalue"); }
	virtual const MTCHAR* getHelpString(){ return _T("datevalue(date_text)");}
	virtual const MTCHAR* getDescription(){ return _T("Converts a date string to a decimal number");}	
	virtual MTDOUBLE convert(const MTSTRING &val)
	{
		COleDateTime dt;
		dt.ParseDateTime(val.c_str(), VAR_DATEVALUEONLY);

		if( dt.m_status != COleDateTime::valid )
		{			
			throwConversionExcep();
			
		}

		return dt.m_dt;
	}

	virtual MTFunctionI* spawn() { return new DateConvFunc(); }
};

class TimeConvFunc : public MTConvFunctionI
{
public:

	
	virtual const MTCHAR* getSymbol(){return _T("timevalue"); }
	virtual const MTCHAR* getHelpString(){ return _T("timevalue(time_text)");}
	virtual const MTCHAR* getDescription(){ return _T("Converts a time string to a decimal number");}	
	virtual MTDOUBLE convert(const MTSTRING &val)
	{
		COleDateTime dt;
		dt.ParseDateTime(val.c_str(), VAR_TIMEVALUEONLY );

		if( dt.m_status != COleDateTime::valid )
		{
			throwConversionExcep();
		}

		return dt.m_dt;
	}

	virtual MTFunctionI* spawn(){ return new TimeConvFunc(); }
};


#endif