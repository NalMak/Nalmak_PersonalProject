#include "..\Include\SceneManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "LineManager.h"
#include "LightManager.h"
IMPLEMENT_SINGLETON(SceneManager)

// 모든 Scene의 정보를 생성,보관,삭제
// AddScene :새로운 Scene등록
// Load : 다음 Scene이동 가능
// CompareCurrentScene : 현재 Scene의 이름을 비교
// SetFirstScene : 진입 Scene설정
void SceneManager::LoadNextScene()
{
	if (m_isLoad)
	{
		assert("Next Scene is Empty" && m_nextScene);
		m_currentScene = m_nextScene;

		m_isLoad = false;
		ObjectManager::GetInstance()->ReleaseScene();
		LightManager::GetInstance()->ResetSkyBox();
		ResourceManager::GetInstance()->ReleaseSceneResouce();

		ResourceManager::GetInstance()->LoadResourcesBySceneFoloderName(m_currentScene->GetSceneName(), false);
		m_currentScene->Initialize();
	}
}

SceneManager::~SceneManager()
{
	Release();
}

HRESULT SceneManager::Initialize()
{
	m_isLoad = false;
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

void SceneManager::Load(const wstring& _name)
{
	m_nextScene = m_sceneList[_name];
	m_isLoad = true;
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
