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
	//m_animController->SetBlendOption(0.f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	m_animController->PlayBlending(Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4"));
	m_character->SetVelocity(0, 0, 0);
}

void LynIdle::UpdateState()
{
	//m_transform->SetPosition(0, 10, 0);
	if (m_animController->GetPlayRemainTime() < 1.f)
	{
		m_animController->SetBlendOption(1.f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		m_animController->PlayBlending(Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4"));
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"turning");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"turning");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_animController->SetBlendOption(0.5f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"run");
		return;
	}
	
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_animController->SetBlendOption(1.f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"run");
		return;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_SPACE))
	{
		m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idleToJump");
		return;
	}
}

void LynIdle::ExitState()
{
}
