//============================================================================
// File: MicroSecondTimer.cpp
// Purpose: This class creates a timer which can be used to time events
//     to the nearest microsecond.  It is more accurate than using the
//     calls to standard time.h functions which only give millisecond
//     accuracy.
// Author: Adapted from code provided by Gregory A. Gibbs
//============================================================================
#include "MicroSecondTimer.h"

//---------------------------------------------
// Default constructor
//---------------------------------------------
MicroSecondTimer::MicroSecondTimer()
{
	// Get the query call execution time for calibrating out
	QueryPerformanceCounter(&m_iStartCounts); 
	QueryPerformanceCounter(&m_iEndCounts);
	// Get the hardware base timer frequency
	QueryPerformanceFrequency(&m_iBaseFrequency); // current frequency
	m_iCalibrationConstant.QuadPart = m_iEndCounts.QuadPart - m_iStartCounts.QuadPart;
}

//---------------------------------------------
// Start the timer
//---------------------------------------------
void MicroSecondTimer::Start()
{
	QueryPerformanceCounter(&m_iStartCounts); 
}

//---------------------------------------------
// Stop the timer
//---------------------------------------------
void MicroSecondTimer::Stop()
{
	QueryPerformanceCounter(&m_iEndCounts);
}

//---------------------------------------------
// Get the elapsed time in seconds
//---------------------------------------------
double MicroSecondTimer::getTime()

{
	//calculate the number of elapsed microseconds
	//seconds = (end counts - start counts - calibration constant) / frequency)
	//Return the number of Elapsed Seconds
	return double((m_iEndCounts.QuadPart - m_iStartCounts.QuadPart - 
					m_iCalibrationConstant.QuadPart)
					/ double(m_iBaseFrequency.QuadPart));
}

//---------------------------------------------
// Handle the timer overhead. This is needed 
//   only if multiple timers are nested, i.e.
//   running simultaneously.
//---------------------------------------------
double	MicroSecondTimer::getOverhead()
{
	//This is the overhead of the timer
	//this is needed only if multiple timers are nested 
	return double(m_iCalibrationConstant.QuadPart / double(m_iBaseFrequency.QuadPart));
}
