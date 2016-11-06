/** *********************************************************************** **
 **                                                                         **
 ** Copyright (C) 2001-2013 Heinz van Saanen                                **
 **                                                                         **
 ** This file may be used under the terms of the GNU General Public         **
 ** License version 3 or later as published by the Free Software Foundation **
 ** and appearing in the file LICENSE.GPL included in the packaging of      **
 ** this file.                                                              **
 **                                                                         **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE **
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR        **
 ** PURPOSE.                                                                **
 **                                                                         **
 ** *********************************************************************** **/

#ifndef _TIMERCLASS_H_
#define _TIMERCLASS_H_

/** Check out header files */
#if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
	#include <windows.h>
	#include <mmsystem.h>
#else
	#include <sys/time.h>
	#include <unistd.h>
#endif


/** *************************************************************************
 ** Linux gcc: g++ -Wall ... [-DDEBUG]
 ** Win/MinGw: g++ -Wall ... -lwinmm [-DDEBUG]
 **
 ** NOTE: An instantiation will start a timer automatically
 ** NOTE: Win-timers at least up to XP/SP2 are still a shame in
 **       terms of real hardcore-precision
 ** NOTE: uticks() and uwait() are destroying current timer state
 **       for performance reasons. So don't intermix them within
 **       other start()/stop() sequences you rely on
 **
 ** Approx. timer overflow limits and their resolutions:
 **
 ** Win32:     50 days       1 msec  theoretically:-)
 ** Win64:     50 days       1 msec  theoretically:-)
 ** Lin32:     72 minutes    1 usec  definitely
 ** Lin64:   585K years      1 usec  definitely
 **
 ** The code looks quite lengthy, but in fact is short because
 ** of the many #ifdefs. Inlining is reasonable therefore
 ** *************************************************************************/
class TIMERS {

	#if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
	DWORD tmp;
	TIMECAPS resolution;
	#else
	struct timeval tvu1, tvu2;
	unsigned long tmp;
	#endif

	double secs;
	#ifdef DEBUG
	bool err;
	#endif

public:
	#if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
	TIMERS();
	#else
	TIMERS() { start(); }
	#endif
	~TIMERS() {}

	inline void start();	// Restart timer manually
	inline double stop();	// Stop and return elapsed time in seconds

	/** Return current timer counter in usec-ticks. Under Windows
	 ** this is a fake and returns msec-ticks*1000 in reality */
	unsigned long uticks();

	/** Block thread execution for n usecs. Under Windows
	 ** this is a fake and waits msec-ticks*1000 in reality */
	void uwait(const unsigned long usecs);

	/** Debugging */
	#ifdef DEBUG
	bool error() { return err; }
	#endif
};


/** *************************************************************************
 ** WINDOWS with a (theoretical) maximum mm-timer resolution of 1 msec
 ** timeGetTime() returns DWORD. So 32 bit unsigned even on 64 bit machines!
 ** *************************************************************************/
#if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
inline TIMERS::TIMERS() {
	secs=0.0;
	#ifdef DEBUG
	err=false;
	#endif
	if(timeGetDevCaps(&resolution, sizeof(TIMECAPS)) == TIMERR_NOERROR)
		start();
	#ifdef DEBUG
	else
		err=true;
	#endif
}

inline void TIMERS::start() {
	if(timeBeginPeriod(1)==TIMERR_NOERROR) {
		tmp=timeGetTime();
		timeEndPeriod(1);
	}
	#ifdef DEBUG
	else
		err=true;
	#endif
}

inline double TIMERS::stop() {
	if(timeBeginPeriod(1)==TIMERR_NOERROR) {
		secs = (timeGetTime()-tmp) / 1000.0;
		timeEndPeriod(1);
	}
	#ifdef DEBUG
	else {
		err=true;
		secs=0.0;
	}
	#endif

	return secs;
}

/** The usec-resolution is faked of course */
inline unsigned long TIMERS::uticks() {
	if(timeBeginPeriod(1)==TIMERR_NOERROR) {
		tmp=timeGetTime();
		timeEndPeriod(1);
		return (unsigned long)tmp*1000UL;
	}
	#ifdef DEBUG
	else
		err=true;
	#endif

	return 0UL;
}

/**  The usec-resolution is faked of course */
inline void TIMERS::uwait(const unsigned long usecs) {
	#ifdef DEBUG
	if(timeBeginPeriod(1)==TIMERR_NOERROR) {
		tmp=timeGetTime();
		timeEndPeriod(1);
	}
	else {
		err=true;
		return;
	}
	const unsigned long to=tmp+usecs/1000;

	while(tmp<to)
		if(timeBeginPeriod(1)==TIMERR_NOERROR) {
			tmp=timeGetTime();
			timeEndPeriod(1);
		}
		else {
			err=true;
			return;
		}
	#else
	if(timeBeginPeriod(1)==TIMERR_NOERROR) {
		tmp=timeGetTime();
		timeEndPeriod(1);
	}
	const unsigned long to=tmp+usecs/1000;

	while(tmp<to)
		if(timeBeginPeriod(1)==TIMERR_NOERROR) {
			tmp=timeGetTime();
			timeEndPeriod(1);
		}
	#endif
}


/** *************************************************************************
 ** LINUX with a maximum timer resolution of 1 usec
 ** foo.tv_usec has type unsigned long. So behaves well on 64 bit machines!
 ** *************************************************************************/
#else
inline void TIMERS::start() {
	secs=0.0;
	#ifdef DEBUG
	err=false;
	if(gettimeofday(&tvu1, NULL))
		err=true;
	#else
	gettimeofday(&tvu1, NULL);
	#endif
}

inline double TIMERS::stop() {
	#ifdef DEBUG
	if(gettimeofday(&tvu2, NULL)) {
		err=true;
		return 0.0;
	}
	#else
	gettimeofday(&tvu2, NULL);
	#endif

	return secs = tvu2.tv_sec-tvu1.tv_sec + (tvu2.tv_usec-tvu1.tv_usec)/1000000.0;
}

inline unsigned long TIMERS::uticks() {
	#ifdef DEBUG
	if(gettimeofday(&tvu1, NULL)) {
		err=true;
		return 0;
	}
	#else
	gettimeofday(&tvu1, NULL);
	#endif

	return tvu1.tv_sec*1000000UL + tvu1.tv_usec;
}

inline void TIMERS::uwait(const unsigned long usecs) {

	#ifdef DEBUG
	if(gettimeofday(&tvu1, NULL)) {
		err=true;
		return;
	}
	const unsigned long to = (tmp = tvu1.tv_sec*1000000UL + tvu1.tv_usec) + usecs;

	while(tmp<to) {
		if(gettimeofday(&tvu1, NULL)) {
			err=true;
			return;
		}
		tmp = tvu1.tv_sec*1000000UL + tvu1.tv_usec;
	}
	#else
	gettimeofday(&tvu1, NULL);
	const unsigned long to = (tmp = tvu1.tv_sec*1000000UL + tvu1.tv_usec) + usecs;

	while(tmp<to) {
		gettimeofday(&tvu1, NULL);
		tmp = tvu1.tv_sec*1000000UL + tvu1.tv_usec;
	}
	#endif

	return;
}

/** WIN/LIN condition */
#endif

/** _TIMERCLASS_H_ */
#endif
