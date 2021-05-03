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
	
	m_animController_upper->PlayBlending("Lyn_P_Std_Mov_Idle");
	m_animController_lower->PlayBlending("Lyn_P_Std_Mov_Idle");

	SetInteger(L"IsBlend", 1);
}

void LynIdle::EnterState()
{
	switch (m_info->m_state)
	{
	case LYN_STATE_BATTLE_STANDARD:
		if (GetInteger(L"IsBlend") == 1)
		{
			m_animController_upper->PlayBlending("Lyn_B_Std_Mov_Idle");
			m_animController_lower->PlayBlending("Lyn_B_Std_Mov_Idle");
		}
		else 
		{
			m_animController_upper->Play("Lyn_B_Std_Mov_Idle");
			m_animController_lower->Play("Lyn_B_Std_Mov_Idle");
		}
		break;
	case LYN_STATE_PEACE_STANDARD:
		if (GetInteger(L"IsBlend") == 1)
		{
			m_animController_upper->PlayBlending("Lyn_P_Std_Mov_Idle");
			m_animController_lower->PlayBlending("Lyn_P_Std_Mov_Idle");
		}
		else
		{
			m_animController_upper->Play("Lyn_P_Std_Mov_Idle");
			m_animController_lower->Play("Lyn_P_Std_Mov_Idle");
		}
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		break;
	default:
		break;
	}


	m_sKeyTimer = 0;
}

void LynIdle::UpdateState()
{
	
	if (m_sKeyTimer > 0.f)
	{
		m_sKeyTimer -= dTime;
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
		{
			SetState(L"backStep");
			return;
		}
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
	{
		m_sKeyTimer = 0.5f;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		SetState(L"verticalCut_l0");
		return;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_TAB))
	{
		SetState(L"spinSlash_start");
		return;
	}

	switch (m_info->m_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		break;
	case LYN_STATE_BATTLE_STANDARD:
	{
		if (m_info->m_battleToPeaceTimer > 0.f && m_info->m_battleToPeaceTimer - dTime <= 0.f)
		{
			SetState(L"battleToPeace");
			return;
		}
		m_info->m_battleToPeaceTimer -= dTime;
		break;
	}
	case LYN_STATE_BATTLE_HIDEBLADE:
	{
		if (m_info->m_battleToPeaceTimer > 0.f && m_info->m_battleToPeaceTimer - dTime <= 0.f)
		{
			SetState(L"battleToPeace");
			return;
		}
		m_info->m_battleToPeaceTimer -= dTime;
		break;
	}
	default:
		break;
	}
}

void LynIdle::ExitState()
{
}
