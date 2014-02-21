#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>

class Timer
{
public:
	Timer() { Initialize(); }
	~Timer() {}

	bool Initialize()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
		if(m_frequency == 0)
			return false;

		m_ticksPerMs = (double)(m_frequency / 1000);
		QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

		return true;

	}

	void StartTimer()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
	}

	double GetTime()
	{
		INT64 currentTime;
		double timeDifference;

		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		timeDifference = (double)(currentTime - m_startTime);
		
		return timeDifference / m_ticksPerMs;
	}

private:
	INT64 m_frequency;
	INT64 m_startTime;
	double m_ticksPerMs;
};


#endif