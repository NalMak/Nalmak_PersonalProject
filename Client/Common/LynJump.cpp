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
	m_jumpDir = 0;
}

void LynJump::EnterState()
{
	if (!m_isUpper)
	{
		m_audio->PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_jump1", L"lyn_jump2"));
	}

	m_character->SetVelocityY(m_info->m_jumpPower);
	m_info->SetSpeed(m_info->m_airSpeed);

	string animName = "";
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		animName = "Mov_IdleToJump_Left";
		m_jumpDir = LYN_MOVE_DIR_STATE::LYN_MOVE_DIR_STATE_LEFT;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		animName = "Mov_IdleToJump_Right";
		m_jumpDir = LYN_MOVE_DIR_STATE::LYN_MOVE_DIR_STATE_RIGHT;
	}
	else
	{
		animName = "Mov_IdleToJump_Front";
		m_jumpDir = LYN_MOVE_DIR_STATE::LYN_MOVE_DIR_STATE_FRONT;
	}
	switch (m_info->GetState())
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
	m_animController->PlayBlending(animName);
	
}

void LynJump::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.05f)
	{
		m_animController->SetBlendOption(0.05f, 1.f, D3DXTRANSITION_LINEAR);
		SetInteger(L"JumpDirection", m_jumpDir);
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
