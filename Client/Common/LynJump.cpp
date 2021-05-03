#include "stdafx.h"
#include "LynJump.h"


LynJump::LynJump()
{
}


LynJump::~LynJump()
{
}

void LynJump::Initialize()
{
}

void LynJump::EnterState()
{
	m_lynMoveControl->SetSpeed(m_info->m_airSpeed);

	m_character->SetVelocityY(m_info->m_jumpPower);

	string animName = "";
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		animName = "Mov_IdleToJump_Left";
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		animName = "Mov_IdleToJump_Right";
	}
	else
	{
		animName = "Mov_IdleToJump_Front";
	}
	switch (m_info->m_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		animName = "Lyn_P_Std_" + animName;
		break;
	case LYN_STATE_BATTLE_STANDARD:
		animName = "Lyn_B_Std_" + animName;
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		animName = "Lyn_B_Hide_" + animName;
		break;
	default:
		break;
	}
	m_animController_lower->PlayBlending(animName);
	
}

void LynJump::UpdateState()
{
	m_lynMoveControl->UpdatePosition();

	m_character->AddVelocity(0, -30 * dTime, 0);

	if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_LOWER))
		return;

	if (m_animController_lower->GetPlayRemainTime() < 0.1f)
	{
		m_animController_lower->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetString(L"preState", L"jump");
		SetState(L"fall");
		return;
	}

	if(m_character->IsGround())
	{
		SetState(L"move");
		return;
	}
}

void LynJump::ExitState()
{
}
