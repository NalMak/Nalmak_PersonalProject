#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "PrototypeManager.h"

//GameObject * GameObject::MakePrototype(wstring _name)
//{
//	GameObject* obj = nullptr;
//
//	obj = new GameObject;
//	assert("Fail to Create GameObject!" && obj);
//	obj->Initialize();
//	obj->m_name = _name;
//	obj->m_dontDestroy = false;
//
//	PrototypeManager::GetInstance()->AddPrototype(_name, obj);
//
//	return obj;
//}

GameObject * GameObject::Instantiate(int _tag, wstring _name)
{
	GameObject* obj = nullptr;

	obj = new GameObject;
	assert("Fail to Create GameObject!" && obj);
	obj->Initialize();
	obj->m_tag = _tag;
	obj->m_name = _name;
	obj->m_dontDestroy = false;



	ObjectManager::GetInstance()->AddObject(obj);

	return obj;
}

GameObject * GameObject::Instantiate(wstring _name)
{
	GameObject* obj = nullptr;

	obj = new GameObject;
	assert("Fail to Create GameObject!" && obj);
	obj->Initialize();
	obj->m_tag = 0;
	obj->m_name = _name;
	obj->m_dontDestroy = false;

	ObjectManager::GetInstance()->AddObject(obj);

	return obj;
}



void GameObject::Destroy(GameObject * _obj)
{
	if (!_obj)
		return;

	_obj->m_dead = true;

	for (auto& com : _obj->m_components)
	{
		com.second->m_isDead = true;
	}
}


//GameObject * GameObject::Instantiate(GameObject * _src)
//{
//	GameObject* clone = nullptr;
//
//	clone = new GameObject;
//	assert("Fail to Create GameObject!" && clone);
//	clone->m_dead = false;
//	clone->m_tag = _src->m_tag;
//	clone->m_name = _src->m_name;
//	clone->m_dontDestroy = _src->m_dontDestroy;
//	clone->m_active = _src->m_active;
//	for (auto& component : _src->m_newComponents)
//	{
//		clone->AddComponent(component);
//	}
//	for (auto& component : _src->m_components)
//	{
//		clone->AddComponent(component);
//	}
//
//	Transform* trs = clone->GetComponent<Transform>();
//	trs->ResetRelative();
//	
//	for (auto& component : clone->m_components)
//	{
//		
//		component.second->m_transform = trs;
//		component.second->m_gameObject = clone;
//		component.second->Initialize();
//	}
//	clone->m_transform = clone->GetComponent<Transform>();
//	ObjectManager::GetInstance()->AddObject(clone);
//
//	return clone;
//}

//GameObject * GameObject::Instantiate(wstring _srcName)
//{
//	GameObject* clone = nullptr;
//	GameObject* src = PrototypeManager::GetInstance()->GetPrototype(_srcName);
//	clone = new GameObject;
//	assert("Fail to Create GameObject!" && clone);
//	clone->m_dead = false;
//	clone->m_tag = src->m_tag;
//	clone->m_name = src->m_name;
//	clone->m_dontDestroy = src->m_dontDestroy;
//	clone->m_active = src->m_active;
//	for (auto& component : src->m_newComponents)
//	{
//		clone->AddComponent(component);
//	}
//	for (auto& component : src->m_components)
//	{
//		clone->AddComponent(component);
//	}
//
//	Transform* trs = clone->GetComponent<Transform>();
//	trs->ResetRelative();
//
//	for (auto& component : clone->m_components)
//	{
//	
//		component.second->m_transform = trs;
//		component.second->m_gameObject = clone;
//		component.second->Initialize();
//	}
//
//	clone->m_transform = clone->GetComponent<Transform>();
//	
//
//
//	ObjectManager::GetInstance()->AddObject(clone);
//
//	return clone;
//}





void GameObject::AddComponent(const pair<string, Component*>& _component)
{
	//pair<string, Component*> copyComponent;
	//copyComponent.first = _component.first;

	//Component* component = (Component*)malloc(_component.second->m_componentSize);
	//memcpy(component, _component.second, _component.second->m_componentSize);
	//component->m_transform = nullptr;
	//component->m_gameObject = nullptr;
	//copyComponent.second = component;

	//m_components.emplace_back(copyComponent);
}

void GameObject::InitializeComponents()
{
	if (m_newComponents.size() > 0)
	{
		for (int i = 0; i < m_newComponents.size(); ++i)
		{

			m_newComponents[i].second->Initialize();
			m_components.emplace_back(m_newComponents[i]);
		}
		
		m_newComponents.clear();
	}
}

void GameObject::OnEnable()
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnEnable();
		}
	}
}

void GameObject::OnDisable()
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnDisable();
		}
	}
}

void GameObject::Initialize()
{
	m_active = true;
	m_dead = false;
	m_name = L"default";

	int m_tag = 0;


	this->AddComponent<Transform>();
	m_transform = GetComponent<Transform>();

}

void GameObject::Update()
{
	InitializeComponents();


	for (auto iter = m_components.begin(); iter != m_components.end();)
	{
		Component* component = (*iter).second;
		if (component->m_isDead)
		{
			ObjectManager::GetInstance()->AddTo_DeleteComponentsCollector(component);
			iter = m_components.erase(iter);
			continue;
		}
		else if (component->m_isActive)
		{
			component->Update();
		}

		++iter;
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->LateUpdate();
		}
	}
}

void GameObject::PreRender()
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->PreRender();
		}
	}
}

void GameObject::PostRender()
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->PostRender();
		}
	}
}


void GameObject::Release()
{
	auto objManager = ObjectManager::GetInstance();
	for (auto& component : m_newComponents)
	{
		objManager->AddTo_DeleteComponentsCollector(component.second);
	}
	for (auto& component : m_components)
	{
		objManager->AddTo_DeleteComponentsCollector(component.second);
	}

	m_newComponents.clear();
	m_components.clear();
}

void GameObject::OnTriggerEnter(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnTriggerEnter(_col);
		}
	}
}

void GameObject::OnTriggerStay(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnTriggerStay(_col);
		}
	}
}

void GameObject::OnTriggerExit(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnTriggerExit(_col);
		}
	}
}

void GameObject::OnCollisionEnter(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnCollisionEnter(_col);
		}
	}
}

void GameObject::OnCollisionStay(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnCollisionStay(_col);
		}
	}
}

void GameObject::OnCollisionExit(Collisions & _col)
{
	for (auto& component : m_components)
	{
		if (component.second->m_isActive)
		{
			component.second->OnCollisionExit(_col);
		}
	}
}



void GameObject::SetParents(Transform * _parents)
{
	m_transform->SetParents(_parents);
}

void GameObject::SetParents(GameObject * _parents)
{
	m_transform->SetParents(_parents->GetTransform());
}

void GameObject::SetDontDestroy(bool _dontDestroy)
{
	m_dontDestroy = _dontDestroy;

	for (UINT i = 0; i < m_transform->GetChildCount(); ++i)
	{
		m_transform->GetChild(i)->GetGameObject()->SetDontDestroy(_dontDestroy);
	}
}

void GameObject::SetActive(bool _active)
{
	if (m_active == _active)
		return;

	m_active = _active;

	if (m_active)
	{
		OnEnable();
	}
	else
	{
		OnDisable();
	}

	for (UINT i = 0; i < m_transform->GetChildCount(); ++i)
	{
		m_transform->GetChild(i)->GetGameObject()->SetActive(_active);
	}


}

bool GameObject::GetActive()
{
	return m_active;
}

void GameObject::SetTag(int _tag)
{
	ObjectManager::GetInstance()->ChangeTag(_tag, this);
}

GameObject* GameObject::SetPosition(const Vector3 & _pos)
{
	m_transform->position = _pos;

	return this;
}

GameObject* GameObject::SetPosition(float _x, float _y, float _z)
{
	m_transform->position = Vector3(_x, _y, _z);

	return this;
}

GameObject * GameObject::SetPosition(float _x, float _y)
{
	m_transform->position = Vector3(_x, _y, m_transform->position.z);

	return this;
}

GameObject* GameObject::SetScale(const Vector3 & _scale)
{
	m_transform->scale = _scale;

	return this;
}

GameObject* GameObject::SetScale(float _x, float _y, float _z)
{
	m_transform->scale = Vector3(_x, _y, _z);

	return this;
}

GameObject * GameObject::SetScale(float _x, float _y)
{
	m_transform->scale = Vector3(_x, _y, m_transform->scale.z);

	return this;
}

GameObject* GameObject::SetRotation(float _xAngle, float _yAngle, float _zAngle)
{
	D3DXQuaternionRotationYawPitchRoll(&m_transform->rotation, Deg2Rad * _yAngle, Deg2Rad * _xAngle, Deg2Rad *_zAngle);

	return this;
}

//void GameObject::ResetCollision()
//{
//	m_collisions.clear();
//	m_preCollisions.clear();
//}
//
//void GameObject::CollisionNotify(Collision _collision)
//{
//	m_collisions.emplace_back(_collision);
//	m_curCollisionState = true;
//}
//
//void GameObject::CollisionUpdate()
//{
//	//현재 충돌한 경우가 없고 이전에 충돌한적이 없는경우 무조건 상태변화가 없음
//	if (m_collisions.size() == 0 && !m_preCollisionState)
//		return;
//
//	Collisions collisionEnter;
//	Collisions collisionStay;
//	Collisions collisionExit;
//
//	if (m_preCollisions.size() < m_collisions.size())
//	{
//		for (auto& curCol : m_collisions)
//		{
//			bool isExist = false;
//			for (auto& preCol : m_preCollisions)
//			{
//				if (preCol.GetGameObject() == curCol.GetGameObject())
//				{
//					collisionStay.emplace_back(curCol);
//					isExist = true;
//					continue;
//				}
//			}
//			if (!isExist)
//				collisionEnter.emplace_back(curCol);
//		}
//	}
//	else
//	{
//		for (auto& preCol : m_preCollisions)
//		{
//			bool isExist = false;
//			for (auto& curCol : m_collisions)
//			{
//				if (preCol.GetGameObject() == curCol.GetGameObject())
//				{
//					collisionStay.emplace_back(preCol)
//					isExist = true;
//					continue;
//				}
//			}
//			if (!isExist)
//				collisionExit.emplace_back(preCol);
//		}
//	}
//	if (collisionEnter.size() > 0)
//		OnTriggerEnter(collisionEnter);
//	if (collisionStay.size() > 0)
//		OnTriggerStay(collisionStay);
//	if (collisionExit.size() > 0)
//		OnTriggerExit(collisionExit);
//
//	m_preCollisions = m_collisions;
//	m_collisions.clear();
//
//	m_preCollisionState = m_curCollisionState;
//	m_curCollisionState = false;
//}
