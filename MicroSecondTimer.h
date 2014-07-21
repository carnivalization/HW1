//============================================================================
// File: MicroSecondTimer.h
// Purpose: This class creates a timer which can be used to time events
//     to the nearest microsecond.  It is more accurate than using the
//     calls to standard time.h functions which only give millisecond
//     accuracy.
// Author: Adapted from code provided by Gregory A. Gibbs
//============================================================================
#ifndef MICROSECONDTIMER_H
#define MICROSECONDTIMER_H

#include <Windows.h>

class MicroSecondTimer
{
	private:
		LARGE_INTEGER	m_iCalibrationConstant;
		LARGE_INTEGER	m_iStartCounts;
		LARGE_INTEGER	m_iEndCounts;
		LARGE_INTEGER	m_iBaseFrequency;
	public:
		MicroSecondTimer();		//default constructor
		void	Start();		//start the timer
		void	Stop();			//Stop the timer
		double	getTime();		//return the elapsed time in seconds
		double	getOverhead();	//return the overhead that this time has
				//The overhead is only needed if you are using multiple times
				//  if multiple timers are used in a loop, the execution time
				//  of one time will add to the time in a second time. The overhead
				//  time can be used to remove the timer execution time from the
				//  first time.  
};
#endif