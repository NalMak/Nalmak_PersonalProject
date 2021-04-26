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
	


	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpLeft");
		return;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpRight");
		return;
	}
	m_animController->Play("Lyn_P_Std_Mov_JumpFront");
}

void LynJump::UpdateState()
{
	if (m_character->IsGround())
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
		{
			SetState(L"jumpToMove");
			return;
		}
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
		{
			SetState(L"jumpToMove");
			return;
		}
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
		{
			SetState(L"jumpToMove");
			return;
		}

		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
		{
			SetState(L"jumpToMove");
			return;
		}
		SetState(L"jumpToIdle");
		return;
	}
}

void LynJump::ExitState()
{
	m_character->SetVelocity(0,0,0);
}
