#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Nalmak_Include.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
#include "DebugManager.h"
#include "ICycle.h"
#include "TimeManager.h"
#include "GameObject.h"
BEGIN(Nalmak) 
class Transform;

class NALMAK_DLL Component : public ICycle
{
	friend class ObjectManager;
	friend class GameObject;
protected:
	explicit Component();
	virtual ~Component();

protected:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void Initialize()override = 0;
	virtual void Update()override = 0;
	virtual void LateUpdate()override;
	virtual void Release()override;
	virtual void PreRender()override;
	virtual void EachRender()override;
	virtual void PostRender()override;

	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerStay(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;

	void OnCollisionEnter(Collision& _col) override;
	void OnCollisionStay(Collision& _col) override;
	void OnCollisionExit(Collision& _col) override;
public:
	template <typename T>
	static Component* Create(typename T::Desc* _desc)
	{
		Component* instance = new T(_desc);
		instance->m_name = typeid(T).name();

		assert("Fail to Create Component" &&instance);
		return instance;
	}
public:
	template <typename T>
	T* GetComponent()
	{
		if (m_gameObject)
		{
			return m_gameObject->GetComponent<T>();
		}
		else
		{
			return nullptr;
		}
	}
	template <typename T>
	const vector<T*> GetComponents()
	{
		if (m_gameObject)
		{
			return m_gameObject->GetComponents<T>();
		}
		else
		{
			return vector<T*>();
		}
	}
	template <typename T>
	void DeleteComponent()
	{
		m_gameObject->DeleteComponent<T>();
	}
	template <typename T>
	void DeleteComponents()
	{
		m_gameObject->DeleteComponents<T>();
	}
	template <typename T>
	GameObject* AddComponent(typename T::Desc* _desc)
	{
		return m_gameObject->AddComponent<T>(_desc);
	}
	template <typename T>
	GameObject* AddComponent()
	{
		typename T::Desc desc;
		return m_gameObject->AddComponent<T>(&desc);
	}

public:
	virtual void SetActive(bool _active);
	bool IsActive();
	bool IsAlive();

protected:
	GameObject* m_gameObject;
	Transform* m_transform;
public:
	void SetPosition(const Vector3& _pos);
	void SetPosition(float _x,float _y, float _z);
	void SetScale(const Vector3& _scale);
	void SetScale(float _x, float _y, float _z);

	void SetGameObject(GameObject* _obj) { assert("Object is nullptr" && _obj); m_gameObject = _obj; }
	virtual void SetTransform(Transform* _transform) { assert("Transform is nullptr" && _transform);  m_transform = _transform; }
public:
	GameObject* GetGameObject() { return m_gameObject; }
	Transform* GetTransform() { return m_transform; }
private:
	const char* m_name;
	bool m_isActive;
	bool m_isDead;

};

END

#endif // !__COMPONENT_H__
