#include "stdafx.h"
#include "LynWait.h"





void LynWait::Initialize()
{
	SetInteger(L"IsBlend", 0);
}

void LynWait::EnterState()
{

	if (m_lynMoveControl->GetCurStateString() == L"idle")
	{
		switch (m_info->m_state)
		{
		case LYN_STATE_BATTLE_STANDARD:
			/*if (GetInteger(L"IsBlend") == 1)
			{
				m_animController_upper->PlayBlending("Lyn_B_Std_Mov_Idle");
				m_animController_lower->PlayBlending("Lyn_B_Std_Mov_Idle");
			}
			else
			{*/
				m_animController_upper->Play("Lyn_B_Std_Mov_Idle");
				m_animController_lower->Play("Lyn_B_Std_Mov_Idle");
			//}
			break;
		case LYN_STATE_PEACE_STANDARD:
			/*if (GetInteger(L"IsBlend") == 1)
			{
				m_animController_upper->PlayBlending("Lyn_P_Std_Mov_Idle");
				m_animController_lower->PlayBlending("Lyn_P_Std_Mov_Idle");
			}
			else
			{*/
				m_animController_upper->Play("Lyn_P_Std_Mov_Idle");
				m_animController_lower->Play("Lyn_P_Std_Mov_Idle");
			//}
		
			break;
		case LYN_STATE_BATTLE_HIDEBLADE:
			break;
		default:
			break;
		}
	}
	else
	{
		AnimationClip* lowerClip = m_animController_lower->GetCurrentPlayAnimation();
		AnimationClip* upperClip = m_animController_upper->GetCurrentPlayAnimation();

		if (lowerClip != upperClip)
		{
			double playTime = m_animController_lower->GetPlayTime();
			if (GetInteger(L"IsBlend") == 0)
				m_animController_upper->Play(lowerClip, playTime);
			else
				m_animController_upper->PlayBlending(lowerClip, playTime);
		}
	}


	m_sKeyTimer = 0;
}

void LynWait::UpdateState()
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

	AnimationClip* lowerClip = m_animController_lower->GetCurrentPlayAnimation();
	AnimationClip* upperClip = m_animController_upper->GetCurrentPlayAnimation();

	if (lowerClip != upperClip)
	{
		double playTime = m_animController_lower->GetPlayTime();
		if(GetInteger(L"IsBlend") == 0)
			m_animController_upper->Play(lowerClip, playTime);
		else
			m_animController_upper->PlayBlending(lowerClip, playTime);
	}
}

void LynWait::ExitState()
{
}
