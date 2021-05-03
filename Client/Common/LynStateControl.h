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

	Vector3 m_inputDir;
	Vector3 m_targetInput;
	LYN_MOVE_DIR_STATE m_dirState;
	float m_targetSpeed;
public:
	void SetSpeed(float _speed);
	void UpdatePosition();
	LYN_MOVE_DIR_STATE UpdateDirection();
	LYN_MOVE_DIR_STATE GetDirectionState();
private:
	Vector3 m_directionState[9] = {
		{ 0, 0, 1 },
		{ 1,0,0 },
		Nalmak_Math::Normalize({ 1,0,1 }),
		{ -1,0,0 },
		Nalmak_Math::Normalize({ -1,0,1 }),
		{ 0,0,-1 },
		Nalmak_Math::Normalize({ 1,0,-1 }),
		Nalmak_Math::Normalize({ -1,0,-1 }),
		{ 0,0,0 }
	};
};

