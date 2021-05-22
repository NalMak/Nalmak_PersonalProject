#pragma once
#include "Component.h"
#include "Event.h"

class RenderManager;
class MeshRenderer;
class DrawGizmo;
class NALMAK_DLL DebuggingMode :
	public Component
{
public:
	struct Desc
	{
		bool createDirectoryMonitor = false;
		bool freeCamera = false;
		wstring directoryMonitorPath = L"";
	};
	

public:
	DebuggingMode(Desc* _desc);
	~DebuggingMode();
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

private:
	BitFlag<DEBUGGING_MODE> m_debuggingMode;
public:
	void ToggleMode(DEBUGGING_MODE _mode);
private:
	class InputManager* m_input;
	RenderManager* m_render;
	GameObject* m_debugLog;
	vector<GameObject*> m_renderTargets;
	GameObject* m_debugCam;
	GameObject* m_mainCam;
	GameObject* m_directoryMonitor;
	GameObject* m_grid;
	class Text* m_debugModeDescObject;
	GameObject* m_pickingObj;
	MeshRenderer* m_pickingOutLine;


	bool m_startOn_freeCamera;
	DrawGizmo* m_pickingGizmoBase;
	PICKING_TYPE m_pickingType;
	GIZMO_TYPE m_gizmoType;
	Event m_event;
private:
	void CheckPicking();
	void CheckFreeCamera();
	void CheckFreeCameraRock();
	void CheckColliderRender();
	void CheckRecordDebugLog();
	void CheckRenderTargetRender();
	void CheckGridRender();
	void CheckTimeStop();
	void UpdateMaterial();
	void UpdateDesc();
	void PickObject();
	void DeletePicking();
	void UpdateOutLine();
	void UpdatePickingObject();
public:
	void AddUpdateMaterialEvent(EventHandler _e);
	void PickObject(GameObject* _obj);
	void AddEvent(EventHandler _e);
	GameObject* GetPickingObject();
	void SetDebugModeActive(DEBUGGING_MODE _mode, bool _active);

};

