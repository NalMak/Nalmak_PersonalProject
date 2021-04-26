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
		m_animController->Play("Lyn_P_Std_Mov_RightToLeft", 0.1f, 1.f);
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->Play("Lyn_P_Std_Mov_LeftToRight", 0.1f, 1.f);
	}
}

void LynTurning::UpdateState()
{
	DEBUG_LOG(L"turning", L"");

	if (m_animController->GetPlayRemainTime() < 0.1)
	{
		SetState(L"run");
		return;
	}

	if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_W) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_A) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_S) &&
		!InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		SetState(L"idle");
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
	m_character->SetVelocity(velocity * m_info->m_turningSpeed);
}

void LynTurning::ExitState()
{
}
