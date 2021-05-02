#pragma once
#include "StateControl.h"
#include "LynState.h"

class LynStateControl :
	public StateControl
{
public:
	struct Desc
	{

	};
public:
	LynStateControl(Desc* _desc);
	~LynStateControl();
private:
	virtual void Initialize() override;
	virtual void Update() override;
public:
	template <typename T>
	StateControl* AddState(wstring _stateName)
	{
		if (m_stateList.end() != m_stateList.find(_stateName))
			assert("State name is already exist" && 0);

		LynState* state = new T;
		state->m_gameObject = m_gameObject;
		state->m_transform = m_transform;
		

		state->m_stateControl = this;
		m_stateList[_stateName] = state;

		return this;
	}
private:
	AnimationController* m_animController_lower;
	AnimationController* m_animController_upper;

	CharacterController* m_character;
	LynInfo* m_info;
};

