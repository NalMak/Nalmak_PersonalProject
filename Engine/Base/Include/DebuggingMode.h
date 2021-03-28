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
};

