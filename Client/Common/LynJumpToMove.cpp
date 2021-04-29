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
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToMove_Left");
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToMove_Right");
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToMove_Front");
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToMove_Back");
	}
	else 
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToMove_Front");
}

void LynJumpToMove::UpdateState()
{
	Vector3 velocity = { 0, 0, 0 };
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		velocity += m_transform->GetForward();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		velocity -= m_transform->GetRight();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		velocity -= m_transform->GetForward();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		velocity += m_transform->GetRight();
	}
	velocity = Nalmak_Math::Normalize(velocity);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		velocity *= m_info->m_airSpeed;
	}
	else
	{
		velocity *= m_info->m_airSpeed;
	}
	m_character->SetVelocityX(velocity.x);
	m_character->SetVelocityZ(velocity.z);

	if (m_animController->GetPlayRemainTime() < 0.05f)
	{
		m_animController->SetBlendOption(0.05f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"run");
		return;
	}
}

void LynJumpToMove::ExitState()
{
	m_character->SetHalfHeight(m_info->m_halfHeight);
}
