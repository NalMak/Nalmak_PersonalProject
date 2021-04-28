#include "stdafx.h"
#include "LynTurning.h"


LynTurning::LynTurning()
{
}


LynTurning::~LynTurning()
{
}

void LynTurning::Initialize()
{
}

void LynTurning::EnterState()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_RightToLeft");
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_LeftToRight");
	}
}

void LynTurning::UpdateState()
{

	if (m_animController->GetPlayRemainTime() < 0.2)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"run");
		return;
	}

	if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_W) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_A) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_S) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	
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
	velocity *= m_info->m_turningSpeed;
	m_character->SetVelocityX(velocity.x);
	m_character->SetVelocityX(velocity.z);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_SPACE))
	{
		m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idleToJump");
		return;
	}
}

void LynTurning::ExitState()
{
}
