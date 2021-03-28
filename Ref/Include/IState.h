#pragma once

#ifndef __ISTATE_H__
#define __ISTATE_H__

#include "Core.h"
class StateControl;

class NALMAK_DLL IState
{
	friend class StateControl;
protected:
	IState();
	virtual ~IState();
private:
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
protected:
	GameObject* m_gameObject;
	Transform* m_transform;
protected:
	void SetState(wstring _stateName);
	void SetInteger(wstring _key, int _value);
	void SetFloat(wstring _key, float _value);
	void SetVector3(wstring _key, const Vector3& _value);
	void SetString(wstring _key, wstring _value);

	int GetInteger(wstring _key);
	float GetFloat(wstring _key);
	const Vector3& GetVector3(wstring _key);
	wstring GetString(wstring _key);

	template <typename T>
	T* GetComponent()
	{
		return m_gameObject->GetComponent<T>();
	}

protected:
	StateControl* m_stateControl;
};

#endif
