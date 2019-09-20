#pragma once
/**
 * @brief The GameTimer class is for calculating the time.
*/
class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;		//the game total time
	float DeltaTime()const;		//the time between every frame

	void Reset();               //use before message loop
	void Start();              //use when cancle pause
	void Stop();              //use when stop
	void Tick();             //use with every frame

private:
	double m_SecondsPerCount;  //the time between counter the unit is second
	double m_DeltaTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_Stopped;
};