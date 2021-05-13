#pragma once

#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__


#include "Nalmak_Include.h"


class NALMAK_DLL TimeManager
{
	DECLARE_SINGLETON(TimeManager)
private:
	TimeManager() = default;
	~TimeManager() = default;
public:
	void Initialize();
	void Reset();
	void Start();
	void Pause();
	void Toggle();
	void Resume();
	void Tick();
public:
	const float GetdeltaTime() const { return m_deltaTime; }
	const float GetEngineTime() const { return m_engineTime; }
	float GetTotalTime();
	bool IsPause() { return m_bStop; }

private:
	float m_deltaTime;
	float m_engineTime;
	LARGE_INTEGER m_countPerSec;

	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_previousTime;
	LARGE_INTEGER m_startTime;

	bool m_bStop;

	double m_timer;
	float m_TotalTime;
};



#endif
