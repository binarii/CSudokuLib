#ifndef _TIMERCLASS_H_
#define _TIMERCLASS_H_

#include <Windows.h>
#pragma comment(lib, "user32.lib")

class TimerClass
{
public:
	TimerClass();
	TimerClass(const TimerClass& other);
	~TimerClass();

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