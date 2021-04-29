#include "stdafx.h"
#include "LynIdleToJump.h"


LynIdleToJump::LynIdleToJump()
{
}


LynIdleToJump::~LynIdleToJump()
{
}

void LynIdleToJump::Initialize()
{
}

void LynIdleToJump::EnterState()
{
	m_character->SetVelocityY(m_info->m_jumpPower);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Left");
		return;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Right");
		return;
	}
	m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Front");
	return;
}

void LynIdleToJump::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"jump");
		return;
	}
}

void LynIdleToJump::ExitState()
{
}
