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
}

void LynIdle::EnterState()
{
	m_animController->Play(Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4"), 0.2f, 1.f);
	m_character->SetVelocity(0, 0, 0);
}

void LynIdle::UpdateState()
{
	//m_transform->SetPosition(0, 10, 0);
	if (m_animController->GetPlayRemainTime() < 0.4)
	{
		m_animController->Play(Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4"),0.4f,1.f);
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		SetState(L"turning");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		SetState(L"turning");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		SetState(L"run");
		return;
	}
	
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		SetState(L"run");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_SPACE))
	{
		SetState(L"idleToJump");
		return;
	}
}

void LynIdle::ExitState()
{
}
