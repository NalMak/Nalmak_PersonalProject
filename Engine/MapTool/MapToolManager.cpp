#include "stdafx.h"
#include "MapToolManager.h"
#include "Nalmak3D_MapControlView.h"

IMPLEMENT_SINGLETON(MapToolManager)

MapToolManager::MapToolManager()
{
}


MapToolManager::~MapToolManager()
{
}

void MapToolManager::SetControlView(Nalmak3D_MapControlView * _view)
{
	m_controlView = _view;
}

void MapToolManager::CreateObject(GameObject * _obj)
{
	m_createdOnMapObjectList.emplace_back(_obj);
}

void MapToolManager::DeleteObject(int _num)
{
	if (m_createdOnMapObjectList.size() < _num)
		return;
	auto iter = m_createdOnMapObjectList.begin();
	for (int i = 0; i < _num; ++i)
	{
		++iter;
	}
	DESTROY((*iter));
	m_createdOnMapObjectList.erase(iter);
}

size_t MapToolManager::GetObjectCount()
{
	return m_createdOnMapObjectList.size();
}

void MapToolManager::SelectObject(GameObject * _obj)
{
	m_selectedObject = _obj;
	m_controlView->UpdateObjectInfo(m_selectedObject);
}

void MapToolManager::SeleteObject(int _index)
{
	if (m_createdOnMapObjectList.size() < _index)
		return;

	m_selectedObject = m_createdOnMapObjectList[_index];
}

GameObject * MapToolManager::GetSelectedObject()
{
	return m_selectedObject;
}
