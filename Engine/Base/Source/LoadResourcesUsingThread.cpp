#include "LoadResourcesUsingThread.h"
#include "SceneManager.h"


LoadResourcesUsingThread::LoadResourcesUsingThread(Desc * _desc)
{
	m_directoryPath = _desc->directionPath;

	if (_desc->directionPath == L"")
	{
		assert(L"Please Set Directory Path!" && 0);
	}
	m_isThreadEnd = false;
}

LoadResourcesUsingThread::~LoadResourcesUsingThread()
{
}

void LoadResourcesUsingThread::Initialize()
{
	InitializeCriticalSection(&m_crt);
	m_thread = (HANDLE)_beginthreadex(nullptr, 0, DoThreadFunc, this, 0, nullptr);

}

void LoadResourcesUsingThread::Update()
{
	//SceneManager::GetInstance()->Load(L"stageSelect");

	//DWORD errCode;
	//GetExitCodeThread(m_thread, &errCode);
	//if (errCode != STILL_ACTIVE)
	//{
	//	m_isThreadEnd = true;
	//	SetActive(false);
	//}
}

void LoadResourcesUsingThread::Release()
{
	WaitForSingleObject(m_thread, INFINITE);
	CloseHandle(m_thread);

	DeleteCriticalSection(&m_crt);
}

bool LoadResourcesUsingThread::IsThreadDone()
{
	return m_isThreadEnd;
}

CRITICAL_SECTION LoadResourcesUsingThread::GetCRT()
{
	return m_crt;
}

unsigned LoadResourcesUsingThread::DoThreadFunc(LPVOID pArg)
{
	LoadResourcesUsingThread* instance = (LoadResourcesUsingThread*)pArg;

	EnterCriticalSection(&instance->GetCRT());

	ResourceManager::GetInstance()->LoadAllResources(instance->m_directoryPath,false);

	instance->m_isThreadEnd = true;

	EnterCriticalSection(&instance->GetCRT());
	_endthreadex(0);
	

	return 0;
}
