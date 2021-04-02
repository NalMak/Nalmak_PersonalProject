#include "stdafx.h"
#include "MapToolManager.h"

#include "ObjectInstallTool.h"
IMPLEMENT_SINGLETON(MapToolManager)

MapToolManager::MapToolManager()
{
}


MapToolManager::~MapToolManager()
{
}

void MapToolManager::SetDebuggingMode(DebuggingMode * _debuggingMode)
{
	m_debugHelper = _debuggingMode;
}

void MapToolManager::SetToolStateControl(StateControl* _state)
{
	m_toolControl = _state;
}

void MapToolManager::SetToolState(const wstring & _str)
{
	m_toolControl->SetState(_str);
}

void MapToolManager::SetControlView(ObjectInstallTool * _view)
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
	if (!_obj)
		return;

	m_selectedObject = _obj;
	for (int i = 0; i < m_createdOnMapObjectList.size(); ++i)
	{
		if (m_createdOnMapObjectList[i] == _obj)
		{
			m_controlView->UpdateObjectInfo(m_selectedObject,i);
			return;
		}
	}

}

void MapToolManager::SeleteObject(int _index)
{
	if (m_createdOnMapObjectList.size() < _index)
		return;

	m_selectedObject = m_createdOnMapObjectList[_index];
	m_controlView->UpdateObjectInfo(m_selectedObject, _index);
}

void MapToolManager::UpdateSelectObjectTransform(GameObject * _obj)
{
	m_controlView->UpdateObjectTransformInfo(_obj);
}

GameObject * MapToolManager::GetSelectedObject()
{
	return m_selectedObject;
}

DebuggingMode * MapToolManager::GetDebuggingObject()
{
	return m_debugHelper;
}

StateControl * MapToolManager::GetToolState()
{
	return m_toolControl;
}
