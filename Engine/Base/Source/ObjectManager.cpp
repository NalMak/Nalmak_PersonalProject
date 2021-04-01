#include "..\Include\ObjectManager.h"
#include "Component.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "PhysicsManager.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(ObjectManager)
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Release();
}



void ObjectManager::Initialize(_OBJECT_TAG _ObjectTag, _OBJECT_LAYER _objectLayer)
{
	m_gameObjectLists.assign(_ObjectTag, list<GameObject*>());
	m_objectLayerCount = _objectLayer;
}

void ObjectManager::Update()
{
	MergeObjectList();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end();)
		{
			if (!(*iter)->IsAlive())
			{
				(*iter)->Release();
				m_willBeDeadObjectList.emplace_back(*iter);
				iter = objList.erase(iter);
				continue;
			}
			if ((*iter)->m_active)
			{
				(*iter)->Update();
			}

			++iter;
		}
	}
}

void ObjectManager::LateUpdate()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->LateUpdate();
			}
		}
	}
}

void ObjectManager::PreRender()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->PreRender();
			}
		}
	}
}

void ObjectManager::PostRender()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->PostRender();
			}
		}
	}
}

void ObjectManager::Release()
{
	MergeObjectList();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			(*iter)->Release();
		}
	}

	for (auto& com : m_willBeDeadComponents)
	{
		SAFE_DELETE(com);
	}
	m_willBeDeadComponents.clear();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		objList.clear();
	}
}

void ObjectManager::ReleaseScene()
{
	MergeObjectList();
	list<GameObject*> dontDestroyNonActivedList;
	list<GameObject*> dontDestroyObjectList;

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end();)
		{
			if ((*iter)->m_dontDestroy)
			{
				dontDestroyObjectList.emplace_back(*iter);
				iter = objList.erase(iter);
			}
			else
			{
				(*iter)->Release();
				++iter;
			}
		}
	}

	for (auto& com : m_willBeDeadComponents)
	{
		SAFE_DELETE(com);
	}
	m_willBeDeadComponents.clear();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		objList.clear();
	}
	for (auto& obj : dontDestroyObjectList)
	{
		m_gameObjectLists[obj->m_tag].emplace_back(obj);
	}
}

void ObjectManager::DeleteInstance()
{
	for (auto& com : m_willBeDeadComponents)
	{
		SAFE_DELETE(com);
	}
	m_willBeDeadComponents.clear();


	for (auto& obj : m_willBeDeadObjectList)
	{
		SAFE_DELETE(obj);
	}
	m_willBeDeadObjectList.clear();
}

void ObjectManager::AddTo_DeleteComponentsCollector(Component * _com)
{
	_com->Release();
	m_willBeDeadComponents.emplace_back(_com);
}

void ObjectManager::DeleteList(_OBJECT_TAG _tag)
{
	for (auto& obj : m_gameObjectLists[_tag])
	{
		GameObject::Destroy(obj);
	}
}



void ObjectManager::AddObject(GameObject * _obj)
{
	assert("Object is nullptr" && _obj);

	

	m_newGameObjectList.emplace_back(_obj);
}

void ObjectManager::ChangeTag(_OBJECT_TAG _tag, GameObject * _obj)
{
	auto iter_begin = m_gameObjectLists[_obj->GetTag()].begin();
	for (; iter_begin != m_gameObjectLists[_obj->GetTag()].end(); ++iter_begin)
	{
		if (*iter_begin == _obj)
		{
			iter_begin = m_gameObjectLists[_obj->GetTag()].erase(iter_begin);
			break;
		}
		if (iter_begin == m_gameObjectLists[_obj->GetTag()].end())
			assert("Can't find object  in List " && 0);
	}

	m_gameObjectLists[_tag].emplace_back(_obj);
}

const list<GameObject*>& ObjectManager::GetObjectList(_OBJECT_TAG _tag)
{
	return m_gameObjectLists[_tag];
}

GameObject * ObjectManager::Find(const wstring& _name)
{
	GameObject* object = nullptr;
	for (auto& objlist : m_gameObjectLists)
	{
		for (auto& obj : objlist)
		{
			if (obj->GetName() == _name)
			{
				object = obj;
				return object;
			}
		}
	}
	assert("Can't find object using that name!" && object);
	return object;
}

GameObject * ObjectManager::Find(_OBJECT_TAG _tag, const wstring& _name)
{
	if (m_gameObjectLists[_tag].empty())
		return nullptr;

	for (auto& obj : m_gameObjectLists[_tag])
	{
		if (obj->GetName() == _name)
		{
			return obj;
		}
	}
	return nullptr;
}

GameObject * ObjectManager::FindFirstObjectbyTag(_OBJECT_TAG _tag)
{
	if (m_gameObjectLists[_tag].empty())
		return nullptr;

	return m_gameObjectLists[_tag].front();
}

GameObject* ObjectManager::PickObjectByMouse(Vector3* _hitPoint)
{
	Camera* cam = RenderManager::GetInstance()->GetMainCamera();
	vector<MeshRenderer*> pickEnableRenderList;
	
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			auto renderer = obj->GetComponent<MeshRenderer>();

			if (!renderer)
				continue;
			if(!renderer->IsActive())
				continue;

			if(!renderer->IsPickingEnable())
				continue;;

			if(renderer->GetMesh()->GetPrimitiveType() == D3DPRIMITIVETYPE::D3DPT_LINELIST)
				continue;
			
			if (!cam->IsInFrustumCulling(renderer))
				continue;

			pickEnableRenderList.emplace_back(renderer);
		}
	}
	if (pickEnableRenderList.size() <= 0)
	{
		return nullptr;
	}

	Vector3 camPos = cam->GetTransform()->GetWorldPosition();
	Vector3 dir = cam->GetCamToMouseWorldDirection();

	return PhysicsManager::GetInstance()->Raycast(_hitPoint, camPos, camPos + dir * 1000, pickEnableRenderList);
}

USHORT ObjectManager::GetObjectLayerCount()
{
	return m_objectLayerCount;
}

void ObjectManager::MergeObjectList()
{
	for (auto& newObj : m_newGameObjectList)
	{
		m_gameObjectLists[newObj->GetTag()].emplace_back(newObj);
	}
	m_newGameObjectList.clear();
}
