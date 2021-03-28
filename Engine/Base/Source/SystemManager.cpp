#include "..\Include\SystemManager.h"
#include "TimeManager.h"
#include "RenderManager.h"

IMPLEMENT_SINGLETON(SystemManager)

SystemManager::SystemManager()
{
	m_device = DeviceManager::GetInstance();
}


SystemManager::~SystemManager()
{
}

void SystemManager::Update()
{
	UpdateFPS();
#ifdef _DEBUG
	UpdateFrequency();
#endif
}

void SystemManager::Log(wstring name, const Vector3 & e)
{
#ifdef _DEBUG
	/*if (m_isRender)
	{
		AutoSortLog("|Type |  ", "Vector3", m_typeColumnLen);
		AutoSortLog("|Name |  ", name, m_nameColumnLen);
		AutoSortLog("|Value|  ", Vector::ToString(e), m_valueColumnLen);
		cout << "+-----+----------------------------------------------------------------------------------------------------------" << endl;
	}*/
#endif
}

void SystemManager::Log(wstring name, const Vector2 & e)
{
#ifdef _DEBUG
	/*if (m_isRender)
	{
		AutoSortLog("|Type |  ", "Vector2", m_typeColumnLen);
		AutoSortLog("|Name |  ", name, m_nameColumnLen);
		AutoSortLog("|Value|  ", Vector::ToString(e), m_valueColumnLen);
		cout << "+-----+----------------------------------------------------------------------------------------------------------" << endl;
	}*/

#endif 
}

void SystemManager::DrawLine()
{
#ifdef _DEBUG
	cout << setw(100) << setfill('-') << endl;
#endif 
}

void SystemManager::UpdateFPS()
{
	static int frameCount = 0;
	static float fTimeElapse = TimeManager::GetInstance()->GetTotalTime();

	frameCount++;

	if (TimeManager::GetInstance()->GetTotalTime() - fTimeElapse >= 1.0f)
	{
		fTimeElapse += 1.0f;
		m_fps = L"  FPS : " + std::to_wstring(frameCount);
		frameCount = 0;
	}
}

void SystemManager::UpdateFrequency()
{
	m_updateTimer += TimeManager::GetInstance()->GetdeltaTime();

	if (m_updateTimer >= 0.5f)
	{
		m_isRender = true;
		m_updateTimer = 0;
	}
	else
		m_isRender = false;
}
