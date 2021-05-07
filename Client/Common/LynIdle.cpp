#include "stdafx.h"
#include "LynIdle.h"

LynIdle::LynIdle()
{
}

LynIdle::~LynIdle()
{
}

void LynIdle::Initialize()
{
	m_animController->PlayBlending("Lyn_P_Std_Mov_Idle");
	SetInteger(L"IsBlend", 0);
	SetInteger(L"JumpDirection", LYN_MOVE_DIR_STATE::LYN_MOVE_DIR_STATE_FRONT);

}

void LynIdle::EnterState()
{
	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE)
	{
		SetState(L"move");
		return;
	}

	string animName;
	switch (m_info->GetState())
	{
	case LYN_STATE_BATTLE_STANDARD:
		animName = "Lyn_B_Std_Mov_Idle";
		break;
	case LYN_STATE_PEACE_STANDARD:
		animName = "Lyn_P_Std_Mov_Idle";
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		animName = "Lyn_B_Hide_Mov_Idle";
		break;
	default:
		break;
	}
	if (GetInteger(L"IsBlend") == 0)
		m_animController->Play(animName);
	else
		m_animController->PlayBlending(animName);

	/*if (GetInteger(L"IsBlend") == 0)
		m_animController->Play(animName);
	else*/

}

void LynIdle::UpdateState()
{
	m_info->UseEnergy(3);

	if (!m_character->IsGround())
	{
		SetInteger(L"JumpDirection", LYN_MOVE_DIR_STATE::LYN_MOVE_DIR_STATE_FRONT);
		SetState(L"fall");
		return;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		SetState(L"jump");
		return;
	}

	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE)
	{
		SetInteger(L"IsBlend", 1);
		SetState(L"move");
		return;
	}
	auto state = m_info->GetState();
	if (m_state != state)
	{
		m_info->UpdateWeapon(state);
		m_state = state;
		string animName;
		switch (m_info->GetState())
		{
		case LYN_STATE_BATTLE_STANDARD:
			animName = "Lyn_B_Std_Mov_Idle";
			break;
		case LYN_STATE_PEACE_STANDARD:
			animName = "Lyn_P_Std_Mov_Idle";
			break;
		case LYN_STATE_BATTLE_HIDEBLADE:
			animName = "Lyn_B_Hide_Mov_Idle";
			break;
		default:
			break;
		}
		if(GetInteger(L"IsBlend") == 0)
			m_animController->Play(animName);
		else
			m_animController->PlayBlending(animName);

	}
}

void LynIdle::ExitState()
{
}
