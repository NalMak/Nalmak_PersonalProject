#include "..\Include\SceneManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "LineManager.h"
#include "LightManager.h"
IMPLEMENT_SINGLETON(SceneManager)

mutex g_mutex;
// 모든 Scene의 정보를 생성,보관,삭제
// AddScene :새로운 Scene등록
// Load : 다음 Scene이동 가능
// CompareCurrentScene : 현재 Scene의 이름을 비교
// SetFirstScene : 진입 Scene설정
void SceneManager::LoadNextScene()
{
	if (m_isLoad != SCENE_LOAD_TYPE_NONE)
	{
		assert("Next Scene is Empty" && m_nextScene);
		m_currentScene = m_nextScene;

		if (m_isLoad == SCENE_LOAD_TYPE_DEFAULT)
		{
			ResourceManager::GetInstance()->ReleaseSceneResouce();
			ResourceManager::GetInstance()->LoadResourcesBySceneFoloderName(m_currentScene->GetSceneName(), false);
			ObjectManager::GetInstance()->ReleaseScene();
			LightManager::GetInstance()->ResetSkyBox();
			m_isLoad = SCENE_LOAD_TYPE_NONE;
			m_currentScene->Initialize();
		}
		else if(m_isLoad == SCENE_LOAD_TYPE_THREAD)
		{
			ResourceManager::GetInstance()->ReleaseSceneResouce();
			InitializeCriticalSection(&m_crt);
			m_thread = (HANDLE)_beginthreadex(nullptr, 0, ExecuteFunc, this, 0, nullptr);
			m_isLoad = SCENE_LOAD_TYPE_NONE;
		}
	}
	if (m_isOver)
	{
		ObjectManager::GetInstance()->ReleaseScene();
		LightManager::GetInstance()->ResetSkyBox();
		m_isOver = false;
		WaitForSingleObject(m_thread, INFINITE);
		CloseHandle(m_thread);
		DeleteCriticalSection(&m_crt);
		m_currentScene->Initialize();
	}
}

void SceneManager::CleanUpScene()
{
	ResourceManager::GetInstance()->LoadResourcesBySceneFoloderName(m_currentScene->GetSceneName(), false);
}


unsigned SceneManager::ExecuteFunc(LPVOID pArg)
{
	SceneManager* instance = (SceneManager*)pArg;

	EnterCriticalSection(&instance->m_crt);

	instance->CleanUpScene();

	instance->m_isOver = true;

	LeaveCriticalSection(&instance->m_crt);
	_endthreadex(0);
	return 0;
}

SceneManager::~SceneManager()
{
	Release();
}

HRESULT SceneManager::Initialize()
{
	m_isLoad = SCENE_LOAD_TYPE_NONE;
	m_sceneLoadProgressPercentage = 0;
	return S_OK;
}

void SceneManager::Update()
{
	LoadNextScene();

	assert(m_currentScene);
	ObjectManager::GetInstance()->Update();
}

void SceneManager::LateUpdate()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->LateUpdate();
}

void SceneManager::Release()
{
	for (auto& scene : m_sceneList)
		SAFE_DELETE(scene.second);



	ObjectManager::GetInstance()->Release();
	RenderManager::GetInstance()->Release();

	
}

void SceneManager::PreRender()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->PreRender();
}

void SceneManager::Render()
{
	assert(m_currentScene);

	RenderManager::GetInstance()->Render();
}

void SceneManager::PostRender()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->PostRender();
}

void SceneManager::DeleteObject()
{
	LineManager::GetInstance()->DeleteLines();
	ObjectManager::GetInstance()->DeleteInstance();
}

void SceneManager::SetFirstScene(const wstring&  _name)
{
	m_currentScene = m_sceneList[_name];
	assert(m_currentScene);
	m_currentScene->Initialize();
}

void SceneManager::Load(const wstring & _name, SCENE_LOAD_TYPE _loadType)
{
	m_nextScene = m_sceneList[_name];
	m_isLoad = _loadType;
	assert("Load Scene Fail! Please Check Scene name or Create Scene in mainGame!" && m_nextScene);
}


void SceneManager::AddScene(const wstring&  _name, Scene* _scene)
{
	if (m_sceneList[_name])
	{
		assert(0 && L"Scene name is already exist");
	}
	_scene->m_sceneName = _name;
	m_sceneList[_name] = _scene;
}

bool SceneManager::CompareCurrentScene(const wstring&  _name)
{
	return m_sceneList[_name] == m_currentScene;
}

Scene * SceneManager::Find_Scene_Name(const wstring & _name)
{
	return nullptr;
}
