#include "TimerClass.h"

TimerClass::TimerClass()
{

}

TimerClass::TimerClass(const TimerClass& other)
{

}

TimerClass::~TimerClass()
{

}

bool TimerClass::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void TimerClass::Update()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;
}

float TimerClass::GetTimeMs()
{
	return m_frameTime;
}

float TimerClass::GetTimeSeconds()
{
	return (m_frameTime / 1000.0f);
}