#include <windows.h>
#include "GameTimer.h"
/**
  * GameTimer class constructor.
  *
*/
GameTimer::GameTimer()
	: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_BaseTime(0), m_StopTime(0),
	m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

/**
  * Caculate the  total time of the game without the pauseTime.
  * @return the total time of the game.
*/
float GameTimer::TotalTime()const
{
	if (m_Stopped)
	{
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}

	else
	{
		return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
}
/**
  * Caculate the  total time of the game without the pauseTime.
  * @return the total time.
*/
float GameTimer::DeltaTime()const
{

	return (float)m_DeltaTime;
}

/**
  * Reset the time.
  * 
*/
void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_PausedTime = 0;
	m_Stopped = false;
}
/**
	* Start to calculate the time.
*/
void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  m_BaseTime       m_StopTime        startTime     
	if (m_Stopped)
	{
		m_PausedTime += (startTime - m_StopTime);

		m_PrevTime = startTime;
		m_StopTime = 0;
		m_Stopped = false;
	}
}

/**
	* Stop the time.
*/
void GameTimer::Stop()
{
	if (!m_Stopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;
		m_Stopped = true;
	}
}
/**
	* calculate the time in per frame.
*/
void GameTimer::Tick()
{
	if (m_Stopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	// Time difference between this frame and the previous.
	m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

	// Prepare for next frame.
	m_PrevTime = m_CurrTime;

	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}