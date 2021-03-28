#include "..\Include\TimeManager.h"

IMPLEMENT_SINGLETON(TimeManager)


void TimeManager::Initialize()
{
	Reset();
	m_bStop = false;
}

void TimeManager::Reset()
{
	QueryPerformanceCounter(&m_startTime);
	QueryPerformanceCounter(&m_currentTime);
	QueryPerformanceCounter(&m_previousTime);
	QueryPerformanceFrequency(&m_countPerSec);

	m_deltaTime = 0;
	m_engineTime = 0;
}

void TimeManager::Start()
{
	Reset();
	Tick();
}



void TimeManager::Pause()
{
	m_bStop = true;
}

void TimeManager::Toggle()
{
	m_bStop ^= true;
}

void TimeManager::Resume()
{
	Reset();
	m_bStop = false;
}

void TimeManager::Tick()
{
	QueryPerformanceCounter(&m_currentTime);
	QueryPerformanceFrequency(&m_countPerSec); // ÃÊ´ç Æ½¼ö¸¦ ¾Ë¾Æ³¿
	m_engineTime = float(m_currentTime.QuadPart - m_previousTime.QuadPart) / m_countPerSec.QuadPart;
	m_previousTime.QuadPart = m_currentTime.QuadPart;

	if (m_bStop)
	{
		m_deltaTime = 0.0;
	}
	else
	{
		m_deltaTime = m_engineTime;
	}


}



float TimeManager::GetTotalTime()
{
	return ((m_currentTime.QuadPart - m_startTime.QuadPart) / static_cast<float>(m_countPerSec.QuadPart));
}
