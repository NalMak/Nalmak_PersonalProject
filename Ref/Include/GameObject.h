#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Nalmak_Include.h"
#include "ICycle.h"

BEGIN(Nalmak)
USING(Nalmak)




class Component;
class Transform;

//#define MAKEPROTOTYPE GameObject::MakePrototype
#define INSTANTIATE GameObject::Instantiate
#define MAKE_STATIC GameObject::MakeStatic
#define DESTROY GameObject::Destroy
typedef pair<string, Component*> ComponentData;

class NALMAK_DLL GameObject : public ICycle
{
	friend class NalmakPxEventCallBack;
	friend class ObjectManager;
	friend class PrototypeManager;

public:

private:
	explicit GameObject() = default;
	~GameObject() = default;

public:
	//static GameObject* MakePrototype(wstring _name);
	static GameObject* Instantiate(USHORT _tag = 0,USHORT _layer =0,  const wstring& _name = L"default");
	static GameObject* Instantiate(wstring _name);
	static GameObject* MakeStatic(wstring _name);
	//static GameObject* Instantiate(GameObject* _prototype);
	//static GameObject* Instantiate(wstring _prototypeName);

	static void Destroy(GameObject* _obj);


	template <typename T>
	GameObject* AddComponent(typename T::Desc* _desc)
	{
		string name = typeid(T).name();

		Component* component = Component::Create<T>(_desc);
		assert(L"Fail to Create Componet!" && component);

		m_newComponents.emplace_back(pair<string, Component*>(name, component));
		component->SetGameObject(this);
		component->SetTransform(m_transform);
		return this;
	}

	template <typename T>
	GameObject* AddComponent()
	{
		string name = typeid(T).name();

		typename T::Desc desc;
		Component* component = Component::Create<T>(&desc);
		assert(L"Fail to Create Componet!" && component);

		m_newComponents.emplace_back(pair<string, Component*>(name, component));
		component->SetGameObject(this);
		component->SetTransform(m_transform);
		return this;
	}
private:
	void AddComponent(const pair<string, Component*>&  _component);
public:
	template <typename T>
	T* GetComponent()
	{
		for (auto& component : m_components)
		{
			if (component.first == typeid(T).name())
			{
				if (component.second->m_isDead == false)
				{
					return (T*)component.second;
				}
			}
				
		}
		for (auto& component : m_newComponents)
		{
			if (component.first == typeid(T).name())
			{
				if (component.second->m_isDead == false)
				{
					return (T*)component.second;
				}
			}
				
		}

		return nullptr;
	}
	template <typename T>
	const vector<T*> GetComponents()
	{
		vector<T*> componentsList;
		for (auto& component : m_components)
		{
			if (component.first == typeid(T).name())
			{
				if (component.second->m_isDead == false)
				{
					componentsList.emplace_back((T*)component.second);
				}
			}

		}
		for (auto& component : m_newComponents)
		{
			if (component.first == typeid(T).name())
			{
				if (component.second->m_isDead == false)
				{
					componentsList.emplace_back((T*)component.second);
				}
			}

		}

		return componentsList;
	}
	template <typename T>
	void DeleteComponent()
	{

		string name = typeid(T).name();
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			if ((*iter).first == typeid(T).name())
			{
				if (!(*iter).second->m_isDead)
				{
					(*iter).second->m_isDead = true;
					return;
				}
			}
		}
	}
	template <typename T>
	void DeleteComponents()
	{
		string name = typeid(T).name();
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			if ((*iter).first == typeid(T).name())
			{
				if (!(*iter).second->m_isDead)
				{
					(*iter).second->m_isDead = true;
				}
			}
		}
	}
public:
	void InitializeComponents();
private:
	void OnEnable() override;
	void OnDisable() override;
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void PreRender() override;
	void PostRender() override;
	void Release() override;

	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerStay(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;

	void OnCollisionEnter(Collision& _col) override;
	void OnCollisionStay(Collision& _col) override;
	void OnCollisionExit(Collision& _col) override;
public:
	void EachRender() override;
	void ResetRender();
private:
	vector<pair<string, Component*>> m_components;
	vector<pair<string, Component*>> m_newComponents;
private:
	Transform* m_transform = nullptr;

public:
	Transform* GetTransform() { assert(L"Isn't Exist Transform!" && m_transform);  return m_transform; }
private:
	bool m_active;
	bool m_dead;
	bool m_static;
	bool m_dontDestroy;
	bool m_isRendered;
	wstring m_name;
	USHORT m_tag;
	USHORT m_layer;
public:
	void SetParents(Transform* _parents, Matrix* _boneMatrix);
	void SetParents(GameObject* _parents, Matrix* _boneMatrix);

	void SetParents(Transform* _parents);
	void SetParents(GameObject* _parents);

	void SetDontDestroy(bool _dontDestroy);
	void SetStatic(bool _static) { m_static = _static; }
	void SetActive(bool _active);
	void SetName(wstring _name) { m_name = _name; }
	void SetTag(USHORT _tag);
	void SetLayer(USHORT _layer);
	bool IsActive() const { return m_active; }
	bool IsAlive() const { return !m_dead; }

	bool IsStatic() const { return m_static; }
	GameObject* SetPosition(const Vector3& _pos);
	GameObject* SetPosition(float _x, float _y, float _z);
	GameObject* SetPosition(float _x, float _y);
	GameObject* SetScale(const Vector3& _scale);
	GameObject* SetScale(float _x, float _y, float _z);
	GameObject* SetScale(float _x, float _y);
	GameObject* SetRotation(float _xAngle, float _yAngle, float _zAngle);
	GameObject* SetRotation(const Quaternion& _rot);

public:
	const wstring GetName() const { return m_name; }
	USHORT GetTag() const { return m_tag; }
	bool GetActive();
	USHORT GetLayer() { return m_layer; }
};




END
#endif // !__GAMEOBJECT_H__
