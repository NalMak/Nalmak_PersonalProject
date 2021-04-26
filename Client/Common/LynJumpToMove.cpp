#include "stdafx.h"
#include "LynJumpToMove.h"


LynJumpToMove::LynJumpToMove()
{
}


LynJumpToMove::~LynJumpToMove()
{
}

void LynJumpToMove::Initialize()
{
}

void LynJumpToMove::EnterState()
{
	m_character->SetHalfHeight(m_info->m_halfHeight);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpToMove_Left");
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpToMove_Right");
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpToMove_Front");
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_animController->Play("Lyn_P_Std_Mov_JumpToMove_Back");
	}
}

void LynJumpToMove::UpdateState()
{
	Vector3 velocity = { 0, 0, 0 };
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		velocity += { 0, 0, 1 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		velocity += { -1, 0, 0 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		velocity += { 0, 0, -1 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		velocity += { 1, 0, 0 };
	}
	velocity = Nalmak_Math::Normalize(velocity);
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_character->SetVelocity(velocity * m_info->m_runBackwardSpeed);
	}
	else
	{
		m_character->SetVelocity(velocity * m_info->m_runForwardSpeed);
	}


	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		SetState(L"run");
		return;
	}
}

void LynJumpToMove::ExitState()
{
	m_character->SetHalfHeight(m_info->m_halfHeight);
}
