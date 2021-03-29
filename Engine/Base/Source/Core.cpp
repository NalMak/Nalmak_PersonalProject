#include "Core.h"

#include "Exception.h"
#include "DeviceManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "SystemManager.h"
#include "DebugManager.h"
#include "Quad.h"
#include "LineVI.h"
#include "Triangle.h"
#include "Core.h"
#include "LineManager.h"
#include "PhysicsManager.h"

USING(Nalmak)

IMPLEMENT_SINGLETON(Core)

// Core changes 02.22 for.jjy
// Device Getter Func 1Add;
// Renderman GetterFunc 2Add;

Core::Core()
{
	m_soundManager = SoundManager::GetInstance();
	m_sceneManager = SceneManager::GetInstance();
	m_prototypeManager = PrototypeManager::GetInstance();
	m_objectManager = ObjectManager::GetInstance();
	m_inputManager = InputManager::GetInstance();
	m_resourceManager = ResourceManager::GetInstance();
	m_timeManager = TimeManager::GetInstance();
	m_lineManager = LineManager::GetInstance();
	m_systemManager = SystemManager::GetInstance();
	m_debugManager = DebugManager::GetInstance();
	m_lightManager = LightManager::GetInstance();
	//
	m_deviceManager = DeviceManager::GetInstance();
	m_renderManager = RenderManager::GetInstance();
	m_physicsManager = PhysicsManager::GetInstance();
	//
}


Core::~Core()
{
	ResourceManager::DestroyInstance();
	SoundManager::DestroyInstance();
	InputManager::DestroyInstance();
	SceneManager::DestroyInstance();
	RenderManager::DestroyInstance();
	LineManager::DestroyInstance();
	PrototypeManager::DestroyInstance();
	ObjectManager::DestroyInstance();
	DeviceManager::DestroyInstance();
	TimeManager::DestroyInstance();
	SystemManager::DestroyInstance();
	DebugManager::DestroyInstance();
	LightManager::DestroyInstance();
	PhysicsManager::DestroyInstance();
}



void Core::Initialize(HINSTANCE _hInst, HWND mainHandle, Desc* _desc, HWND inputHandle)
{
	if (!inputHandle)
		inputHandle = mainHandle;

	RenderManager::GetInstance()->SetWindowSize(_desc->wincx, _desc->wincy);
	ObjectManager::GetInstance()->Initialize(_desc->OBJECT_TAG_COUNT);
	DeviceManager::GetInstance()->Initialize(_desc->wincx, _desc->wincy, mainHandle, _desc->windowMode);

	m_soundManager->Initialize();

	m_resourceManager->CreateDefaultResource();
	m_resourceManager->Initialize(_desc->LoadAllResource_OnAwake, _desc->resourceDirectoryPath);

	RenderManager::GetInstance()->Initialize();
	LightManager::GetInstance()->Initialize();

	m_inputManager->Initialize(_hInst, inputHandle);
	m_lineManager->Initialize();
	m_physicsManager->Initialize();
	m_timeManager->Initialize();
}

void Core::Run()
{
	
	m_timeManager->Tick();
	m_systemManager->Update();
	m_soundManager->Update();
	m_inputManager->Update();

	m_sceneManager->Update();
	m_physicsManager->Update();
	m_sceneManager->LateUpdate();

	m_sceneManager->PreRender();

	m_sceneManager->Render();
	//m_sceneManager->PostRender();
	m_sceneManager->DeleteObject();
}

void Core::SetStartScene(const wstring& _name)
{
	m_resourceManager->LoadResourcesByFoloderName(L"static", false);
	m_resourceManager->LoadResourcesByFoloderName(_name, false);

	m_sceneManager->SetFirstScene(_name);
}

void Core::AddScene(const wstring& _name, Scene * _scene)
{
	m_sceneManager->AddScene(_name, _scene);
}



void Core::LoadScene(const wstring& _name)
{
	m_sceneManager->Load(_name);
}



void Core::DrawLine(const Vector3 & _start, const Vector3 & _end, DEBUG_COLOR _debugColor)
{
	m_lineManager->DrawLine(_start, _end, _debugColor);
}






GameObject * Core::GetPrototype(const wstring& _name)
{
	return m_prototypeManager->GetPrototype(_name);
}

void Core::ActivateCollisionByLayer(_COLLISION_LAYER _layer1, _COLLISION_LAYER _layer2)
{
}

GameObject * Core::FindFirstObject(_OBJECT_TAG _tag)
{
	return m_objectManager->FindFirstObjectbyTag(_tag);
}

GameObject * Core::FindObjectByName(_OBJECT_TAG _tag, const wstring& name)
{
	return m_objectManager->Find(_tag, name);
}

GameObject * Core::PickObjectByMouse()
{
	return m_objectManager->PickObjectByMouse();
}

list<GameObject*> Core::GetObjectList(_OBJECT_TAG _tag)
{
	return m_objectManager->GetObjectList(_tag);
}

Camera * Core::GetMainCamera()
{
	return m_renderManager->GetMainCamera();
}

UINT Core::GetWindowWidth()
{
	return m_renderManager->GetWindowWidth();
}

UINT  Core::GetWindowHeight()
{
	return m_renderManager->GetWindowHeight();
}

void Core::SetWindowSize(UINT _wincx, UINT _wincy)
{
	m_renderManager->SetWindowSize(_wincx, _wincy);
}


HWND  Core::GetHWND()
{
	return m_deviceManager->GetHWND();
}

const wstring & Core::GetResourceDirectoryPath()
{
	return m_resourceManager->GetResourceDirectoryPath();
}

void Core::SetSkyBox(const wstring & _skyBoxName)
{
	m_lightManager->SetSkyBox(_skyBoxName);
}





