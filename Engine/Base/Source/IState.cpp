#include "..\Include\IState.h"

#include "StateControl.h"

IState::IState()
	:m_gameObject(nullptr), m_transform(nullptr), m_stateControl(nullptr)
{
}


IState::~IState()
{
}

void IState::SetState(wstring _stateName)
{
	m_stateControl->SetState(_stateName);
}

void IState::SetInteger(wstring _key, int _value)
{
	m_stateControl->SetInteger(_key, _value);
}

void IState::SetFloat(wstring _key, float _value)
{
	m_stateControl->SetFloat(_key, _value);
}

void IState::SetVector3(wstring _key, const Vector3 & _value)
{
	m_stateControl->SetVector3(_key, _value);
}

void IState::SetString(wstring _key, wstring _value)
{
	m_stateControl->SetString(_key, _value);
}

int IState::GetInteger(wstring _key)
{
	return m_stateControl->GetInteger(_key);
}

float IState::GetFloat(wstring _key)
{
	return m_stateControl->GetFloat(_key);
}

const Vector3 & IState::GetVector3(wstring _key)
{
	return m_stateControl->GetVector3(_key);
}

wstring IState::GetString(wstring _key)
{
	return m_stateControl->GetString(_key);
}

