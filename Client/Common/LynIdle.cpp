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
	m_animController->PlayBlending(animName);



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
	auto dirState = m_info->GetDirectionState();
	if (dirState == LYN_MOVE_DIR_STATE_RIGHT)
	{
		SetState(L"rebound");
		return;
	}
	else if (dirState == LYN_MOVE_DIR_STATE_LEFT)
	{
		SetState(L"rebound");
		return;
	}
	else if (dirState != LYN_MOVE_DIR_STATE_NONE)
	{
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
		m_animController->PlayBlending(animName);

	}
}

void LynIdle::ExitState()
{
}
