#ifndef _FUNC_INCLUDED
#define _FUNC_INCLUDED

#include "..\..\..\MTParserLib\MTParserPrivate.h"
#include <math.h>

class DateFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("date"); }

	virtual const MTCHAR* getHelpString(){ return _T("date(year, month, day)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns a number representing this date"); }	
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt;
		dt.SetDate(pArg[0], pArg[1], pArg[2]);
		return dt.m_dt;
	}

	virtual MTFunctionI* spawn() { return new DateFunc(); }

};

class TimeFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("time"); }

	virtual const MTCHAR* getHelpString(){ return _T("time(hour, minute, second)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns a number representing this time"); }	
	virtual int getNbArgs(){ return 3; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt;
		dt.SetTime(pArg[0], pArg[1], pArg[2]);
		return dt.m_dt;
	}

	virtual MTFunctionI* spawn() { return new TimeFunc(); }

};

class DayFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("day"); }

	virtual const MTCHAR* getHelpString(){ return _T("day(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the day of the month corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetDay();
	}

	virtual MTFunctionI* spawn() { return new DayFunc(); }

};

class HourFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("hour"); }

	virtual const MTCHAR* getHelpString(){ return _T("hour(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the number of hours corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetHour();
	}

	virtual MTFunctionI* spawn() { return new HourFunc(); }

};

class MinuteFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("minute"); }

	virtual const MTCHAR* getHelpString(){ return _T("minute(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the number of minutes corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetMinute();
	}

	virtual MTFunctionI* spawn() { return new MinuteFunc(); }

};

class SecondFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("second"); }

	virtual const MTCHAR* getHelpString(){ return _T("second(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the number of second corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetSecond();
	}

	virtual MTFunctionI* spawn() { return new SecondFunc(); }

};

class YearFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("year"); }

	virtual const MTCHAR* getHelpString(){ return _T("year(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the year corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetYear();
	}

	virtual MTFunctionI* spawn() { return new YearFunc(); }

};

class MonthFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("month"); }

	virtual const MTCHAR* getHelpString(){ return _T("month(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the month corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetMonth();
	}

	virtual MTFunctionI* spawn() { return new MonthFunc(); }

};

class DayOfWeekFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("weekday"); }

	virtual const MTCHAR* getHelpString(){ return _T("weekday(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the day of the week (1:sunday..7:saturday) corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetDayOfWeek();
	}

	virtual MTFunctionI* spawn() { return new DayOfWeekFunc(); }

};

class DayOfYearFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("yearday"); }

	virtual const MTCHAR* getHelpString(){ return _T("yearday(date_value)"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns the day of the year (January 1 = 1) corresponding to this date value"); }	
	virtual int getNbArgs(){ return 1; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		COleDateTime dt(pArg[0]);
		return dt.GetDayOfYear();
	}

	virtual MTFunctionI* spawn() { return new DayOfYearFunc(); }

};

class NowDateFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("nowdate"); }

	virtual const MTCHAR* getHelpString(){ return _T("nowdate()"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns today's date"); }	
	virtual int getNbArgs(){ return 0; }
	virtual bool isConstant(){ return false; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		time_t curTime;   
		time(&curTime);   
		
		COleDateTime dt(curTime);
		return (int)dt.m_dt;	// only the date by cutting the decimal part 
	}

	virtual MTFunctionI* spawn() { return new NowDateFunc(); }

};

class NowTimeFunc : public MTFunctionI
{		
	
	virtual const MTCHAR* getSymbol(){return _T("nowtime"); }

	virtual const MTCHAR* getHelpString(){ return _T("nowtime()"); }
	virtual const MTCHAR* getDescription(){ return _T("Returns current time"); }	
	virtual int getNbArgs(){ return 0; }
	virtual bool isConstant(){ return false; }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		time_t curTime;   
		time(&curTime);   
		
		COleDateTime dt(curTime);
		return fmod(dt.m_dt, (int)dt.m_dt);
	}

	virtual MTFunctionI* spawn() { return new NowTimeFunc(); }

};


#endif