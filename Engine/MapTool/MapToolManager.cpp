#include "stdafx.h"
#include "MapToolManager.h"

#include "ObjectInstallTool.h"
#include "AnimationController.h"

IMPLEMENT_SINGLETON(MapToolManager)

MapToolManager::MapToolManager()
{
}


MapToolManager::~MapToolManager()
{
}

void MapToolManager::ActiveAnimationObject(bool _active)
{
	if (!m_animationObject)
	{
		m_animationObject = INSTANTIATE();
		m_animationObject->SetActive(false);
	}
	else
	{
		m_animationObject->SetActive(_active);
	}
}

void MapToolManager::PickObject(GameObject * _obj)
{
	m_debugHelper->PickObject(_obj);
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

void MapToolManager::DeleteAllObject()
{
	for (auto& obj : m_createdOnMapObjectList)
	{
		DESTROY(obj);
	}
	
	m_createdOnMapObjectList.clear();
}

size_t MapToolManager::GetObjectCount()
{
	return m_createdOnMapObjectList.size();
}

GameObject * MapToolManager::GetGameObject(int _index)
{
	return m_createdOnMapObjectList[_index];
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
	m_debugHelper->PickObject(m_selectedObject);
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

GameObject * MapToolManager::GetAnimationObject()
{
	return m_animationObject;
}

void MapToolManager::SetAnimationObjectMesh(const wstring & _meshName)
{

	if (m_animationObject->GetComponent<SkinnedMeshRenderer>())
	{
		m_animationObject->DeleteComponent<SkinnedMeshRenderer>();
	}
	if(m_animationObject->GetComponent<AnimationController>())
	{
		m_animationObject->DeleteComponent<AnimationController>();
	}
	SkinnedMeshRenderer::Desc renderer;
	renderer.meshName = _meshName;
	AnimationController::Desc anim;
	anim.meshName = _meshName;
	m_animationObject->AddComponent<AnimationController>(&anim);
	m_animationObject->AddComponent<SkinnedMeshRenderer>(&renderer);
	m_animationObject->GetComponent<SkinnedMeshRenderer>()->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FREE_PASS);
	m_animationObject->SetActive(true);

	//m_animationObject->GetComponent<Animator>()->
}



