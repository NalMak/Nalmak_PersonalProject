#pragma once
#include "GameObject.h"

class ObjectInstallTool;

class MapToolManager
{
	DECLARE_SINGLETON(MapToolManager)
public:
	MapToolManager();
	~MapToolManager();

private:
	StateControl* m_toolControl = nullptr;
	GameObject* m_selectedObject = nullptr;
	GameObject* m_animationObject = nullptr;

	vector<GameObject*> m_createdOnMapObjectList;
	ObjectInstallTool* m_controlView;
	DebuggingMode* m_debugHelper;
public:
	void ActiveAnimationObject(bool _active);
	void PickObject(GameObject* _obj);
	void SetDebuggingMode(DebuggingMode* _debuggingMode);
	void SetToolStateControl(StateControl* _state);
	void SetToolState(const wstring& _str);
	void SetControlView(ObjectInstallTool* _view);
	void CreateObject(GameObject* _obj);
	void DeleteObject(int _num);
	void DeleteAllObject();
	size_t GetObjectCount();
	GameObject* GetGameObject(int _index);
	void SelectObject(GameObject* _obj);
	void SeleteObject(int _index);
	void UpdateSelectObjectTransform(GameObject* _obj);
	GameObject* GetSelectedObject();
	DebuggingMode* GetDebuggingObject();
	StateControl* GetToolState();
	GameObject* GetAnimationObject();
	void SetAnimationObjectMesh(const wstring& _meshName);
};

