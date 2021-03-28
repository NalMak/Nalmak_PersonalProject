#pragma once
#include "GameObject.h"

class Nalmak3D_MapControlView;

class MapToolManager
{
	DECLARE_SINGLETON(MapToolManager)
public:
	MapToolManager();
	~MapToolManager();

private:
	GameObject* m_selectedObject = nullptr;
	vector<GameObject*> m_createdOnMapObjectList;
	Nalmak3D_MapControlView* m_controlView;
public:
	void SetControlView(Nalmak3D_MapControlView* _view);
	void CreateObject(GameObject* _obj);
	void DeleteObject(int _num);
	size_t GetObjectCount();
	void SelectObject(GameObject* _obj);
	void SeleteObject(int _index);
	GameObject* GetSelectedObject();
};

