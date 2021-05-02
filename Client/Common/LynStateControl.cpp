#include "stdafx.h"
#include "LynStateControl.h"



LynStateControl::LynStateControl(Desc * _desc)
	:StateControl(&StateControl::Desc())
{
}

LynStateControl::~LynStateControl()
{
}

void LynStateControl::Initialize()
{
	m_character = GetComponent<CharacterController>();
	m_info = GetComponent<LynInfo>();
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];

	for(auto& state : m_stateList)
	{
		LynState* lynState = (LynState*)(state.second);
		lynState->m_character = m_character;
		lynState->m_info = m_info;
		lynState->m_animController_lower = m_animController_lower;
		lynState->m_animController_upper = m_animController_upper;
	}
	
	StateControl::Initialize();
}

void LynStateControl::Update()
{

	/*if (!m_character->IsGround())
	{
		if (!CompareState(L"jump"))
		{
			SetState(L"jump");
			return;
		}
	}*/
	DEBUG_LOG(L"Current State", GetCurStateString());
	StateControl::Update();
}
