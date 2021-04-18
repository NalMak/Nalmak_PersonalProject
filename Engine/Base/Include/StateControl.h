#pragma once

#ifndef  __STATECONTROL_H__
#define __STATECONTROL_H__

#include "Component.h"
#include "Nalmak_Include.h"
class IState;

class NALMAK_DLL StateControl :
	public Component
{
public:
	struct Desc
	{

	};
public:
	StateControl(Desc* _desc);
	~StateControl();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

public:
	template <typename T>
	StateControl* AddState(wstring _stateName)
	{
		if (m_stateList.end() != m_stateList.find(_stateName))
			assert("State name is already exist" && 0);

		IState* state = new T;
		state->m_gameObject = m_gameObject;
		state->m_transform = m_transform;


		state->m_stateControl = this;
		m_stateList[_stateName] = state;

		return this;
	}

	template <class T>
	T*	GetState(const wstring& _stateName)
	{
		auto state = m_stateList.find(_stateName);

#ifdef _DEBUG
		if (state == m_stateList.end())
		{
			assert(L"can't find state");
		}
#endif

		T* castState = static_cast<T*>(state->second);
		return castState;
	}

	wstring GetCurStateString();
	void InitState(wstring _stateName);
	void SetState(const wstring& _stateName);
	bool CompareState(wstring _stateName);

	void SetInteger(wstring _key, int _value);
	void SetFloat(wstring _key, float _value);
	void SetVector3(wstring _key, const Vector3& _value);
	void SetString(wstring _key, const wstring& _value);

	void AddInteger(wstring _key, int _addValue);
	void AddFloat(wstring _key, float _addValue);

	int GetInteger(wstring _key);
	float GetFloat(wstring _key);
	const Vector3& GetVector3(wstring _key);
	const wstring& GetString(wstring _key);
private:
	IState* m_state;
	map<wstring, IState*> m_stateList;


	map<wstring, int>		m_blackBoardInteger;
	map<wstring, float>		m_blackBoardFloat;
	map<wstring, Vector3>	m_blackBoardVector3;
	map<wstring, wstring>	m_blackBoardString;
};

#endif // ! __STATECONTROL_H__
