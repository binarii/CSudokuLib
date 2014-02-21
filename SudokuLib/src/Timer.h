#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>
#pragma comment(lib, "user32.lib")

class Timer
{
public:
	Timer();
	Timer(const Timer& other);
	~Timer();

	bool Initialize();
	void Update();

	float GetTimeMs();
	float GetTimeSeconds();

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};

#endif