#pragma once
#include "Component.h"
class RenderManager;
class MeshRenderer;

class NALMAK_DLL DebuggingMode :
	public Component
{
public:
	struct Desc
	{

	};
	enum PICKING_TYPE
	{
		PICKING_TYPE_NONE = -1,
		PICKING_TYPE_RIGHT,
		PICKING_TYPE_UP,
		PICKING_TYPE_LOOK,
		PICKING_TYPE_MAX
	};
	enum GIZMO_TYPE
	{
		GIZMO_TYPE_POSITION,
		GIZMO_TYPE_ROTATION,
		GIZMO_TYPE_SCALE,
		GIZMO_TYPE_MAX
	};
public:
	DebuggingMode(Desc* _desc);
	~DebuggingMode();
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

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
	GameObject* m_grid;
	class Text* m_debugModeDescObject;
	GameObject* m_pickingObj;
	MeshRenderer* m_pickingOutLine;
	class GameObject* m_pickingGizmo[3];
	class GameObject* m_pickingGizmoBase;
	PICKING_TYPE m_pickingType;
	GIZMO_TYPE m_gizmoType;
private:
	void CheckPicking();
	void CheckFreeCamera();
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
	DebuggingMode::PICKING_TYPE IsGizmoPicking();
};

