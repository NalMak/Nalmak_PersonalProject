#pragma once


#ifndef __CORE_H__
#define __CORE_H__

#include <windows.h>

#pragma comment(lib, "fmodex64_vc.lib")

#include "Nalmak_Struct.h"
#include "Nalmak_Define.h"
#include "Nalmak_Extern.h"
#include "Nalmak_Struct.h"

#include "SceneManager.h"
#include "PrototypeManager.h"
#include "GameObject.h"	
#include "ObjectManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "LightManager.h"
#include "SoundManager.h"

#include "BitFlag.h"
#include "Exception.h"
#include "FileIO.h"
#include "SplineCurve.h"
#include "IState.h"

#pragma region Component
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "FreeMove.h"
#include "Grid.h"
#include "Text.h"
#include "SystemInfo.h"
#include "ParticleRenderer.h"
#include "DrawGizmo.h"
#include "DrawGizmo_2D.h"
#include "StateControl.h"
#include "Button.h"
#include "Animator.h"
#include "Terrain.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "CanvasRenderer.h"
#include "SingleImage.h"
#include "CanvasPicking.h"
#include "DeviceManager.h"
#include "RenderManager.h"
#include "Toggle.h"
#include "Slider.h"
#include "Number.h"
#include "TrailRenderer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "LoadResourcesUsingThread.h"
#include "DebuggingMode.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "CapsuleCollider.h"
#include "RigidBody.h"
#include "DebugObject.h"
#pragma endregion

//#define __SOUND_ON__


class CollisionManager;
class SystemManager;
class PhysicsManager;
BEGIN(Nalmak)

class NALMAK_DLL Core
{
	DECLARE_SINGLETON(Core)
private:
	Core();
	~Core();
public:

	struct Desc
	{
		UINT wincx = 1920;
		UINT wincy = 1080;
		bool windowMode = true;
		wstring startSceneName;
		bool LoadAllResource_OnAwake = false;
		wstring resourceDirectoryPath = L"../../Resource";
		_OBJECT_TAG OBJECT_TAG_COUNT = 1;
		_RENDER_LAYER RENDER_LAYER_COUNT = 1;
		_COLLISION_LAYER COLLISION_LAYER_COUNT = 1;
	};
public:
	void Initialize(HINSTANCE _hInst, HWND mainHandle,  Desc* _desc, HWND inputHandle = nullptr);
	void Run();

public:
	void SetStartScene(const wstring& _name);
	void AddScene(const wstring& _name, Scene* _scene);
	void LoadScene(const wstring& _name);
public:
	void DrawLine(const Vector3& _start, const Vector3& _end, DEBUG_COLOR = DEBUG_COLOR_GREEN);
public:
	GameObject* GetPrototype(const wstring& _name);
public:
	void ActivateCollisionByLayer(_COLLISION_LAYER _layer1, _COLLISION_LAYER _layer2);
public:
	// Search
	GameObject* FindFirstObject(_OBJECT_TAG _tag);
	GameObject* FindObjectByName(_OBJECT_TAG _tag, const wstring& name);
	GameObject* PickObjectByMouse(Vector3* _hitPoint);
	list<GameObject*> GetObjectList(_OBJECT_TAG _tag);
	Camera* GetMainCamera();
public:
	UINT GetWindowWidth();
	UINT GetWindowHeight();
	void SetWindowSize(UINT _wincx, UINT _wincy);

public:
	HWND GetHWND();
public:
	const wstring& GetResourceDirectoryPath();


	// Environment Setting
public:
	void SetSkyBox(const wstring& _skyBoxName);
private:
	SoundManager* m_soundManager;
	SceneManager* m_sceneManager;
	PrototypeManager* m_prototypeManager;
	ObjectManager* m_objectManager;
	InputManager* m_inputManager;
	ResourceManager* m_resourceManager;
	SystemManager* m_systemManager;
	DebugManager* m_debugManager;
	//CollisionManager* m_collisionManager;
	LightManager* m_lightManager;
	TimeManager* m_timeManager;
	LineManager* m_lineManager;
	PhysicsManager* m_physicsManager;
private:
	DeviceManager* m_deviceManager;
	RenderManager* m_renderManager;

	

};

END


#endif
