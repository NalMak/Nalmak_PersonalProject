#include "stdafx.h"
#include "LynJumpToIdle.h"


LynJumpToIdle::LynJumpToIdle()
{
}


LynJumpToIdle::~LynJumpToIdle()
{
}

void LynJumpToIdle::Initialize()
{
}

void LynJumpToIdle::EnterState()
{
	m_animController->PlayBlending("Lyn_P_Std_Mov_JumpToIdle");
}

void LynJumpToIdle::UpdateState()
{
	/*float ratio = abs(m_animController->GetPlayRatio() * 2 - 1);
	
	m_height = Nalmak_Math::Lerp(  m_info->m_jumpHalfHeight, m_info->m_halfHeight, ratio);
	m_height = Nalmak_Math::Clamp(m_height, m_info->m_jumpHalfHeight, m_info->m_halfHeight);
	m_character->SetHalfHeight(m_height);
	*/
	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
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
}

void LynJumpToIdle::ExitState()
{
	/*m_height = m_info->m_halfHeight;
	m_character->SetHalfHeight(m_height);*/
}
