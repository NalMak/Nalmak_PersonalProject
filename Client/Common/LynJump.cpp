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
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpLeft");
		return;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_JumpRight");
		return;
	}
	m_animController->PlayBlending("Lyn_P_Std_Mov_JumpFront");
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
	velocity *= m_info->m_airSpeed;
	m_character->SetVelocityX(velocity.x);
	m_character->SetVelocityZ(velocity.z);


}

void LynJump::ExitState()
{
	m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	m_character->SetVelocity(0,0,0);
}
