#include "DirectoryMonitoring.h"
#include "DebugManager.h"



DirectoryMonitoring::DirectoryMonitoring(Desc * _desc)
{
	m_eventHandle = nullptr;
	m_directoryPath = _desc->directoryPath;
	m_event = _desc->changeMaterialEvent;

}

DirectoryMonitoring::~DirectoryMonitoring()
{
}

void DirectoryMonitoring::Initialize()
{
	m_isChange = false;
	m_isThreadDone = false;

	m_eventHandle = FindFirstChangeNotification(m_directoryPath.c_str(), true, FILE_NOTIFY_CHANGE_LAST_WRITE);

	assert(L"UnExpected nullptr from FindFirstChangeNotification!" && m_eventHandle);

	InitializeCriticalSection(&m_crt);
	m_thread = (HANDLE)_beginthreadex(nullptr, 0, DoThreadFunc, this, 0, nullptr);

}

void DirectoryMonitoring::Update()
{
	if (m_isChange)
	{
		ResourceManager::GetInstance()->UpdateMaterial(m_directoryPath, false);
		UpdateMaterial();
		m_isChange = false;
	}
}

void DirectoryMonitoring::Release()
{
	m_isThreadDone = true;

	FindCloseChangeNotification(m_eventHandle);

	WaitForSingleObject(m_thread, INFINITE);
	CloseHandle(m_thread);
	DeleteCriticalSection(&m_crt);

	m_event.Release();
}

void DirectoryMonitoring::StopMonitoring()
{
	Release();
}

void DirectoryMonitoring::ResumeMonitorion()
{

	Initialize();
}

void DirectoryMonitoring::UpdateMaterial()
{
	if (m_event.GetHandler(0))
	{
		m_event.DoEvent(0);
	}

	
}

unsigned DirectoryMonitoring::DoThreadFunc(LPVOID pArg)
{
	DirectoryMonitoring* instance = (DirectoryMonitoring*)pArg;

	EnterCriticalSection(&instance->m_crt);

	while (true)
	{
		DWORD status = WaitForSingleObject(instance->m_eventHandle, INFINITE);

		if (instance->m_isThreadDone)
			break;

		if (status == WAIT_OBJECT_0)
		{
			instance->m_isChange = true;
		}
		FindNextChangeNotification(instance->m_eventHandle);
	}

	EnterCriticalSection(&instance->m_crt);

	_endthreadex(0);


	return 0;
}
