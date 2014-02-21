#include "Timer.h"

Timer::Timer()
{
	Initialize();
}

Timer::Timer(const Timer& other)
{

}

Timer::~Timer()
{

}

bool Timer::Initialize()
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

void Timer::Update()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;
}

float Timer::GetTimeMs()
{
	return m_frameTime;
}

float Timer::GetTimeSeconds()
{
	return (m_frameTime / 1000.0f);
}