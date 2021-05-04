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

	SetString(L"preState", L"");
}

void LynIdle::EnterState()
{
	m_idleTime = 0.5f;
	m_eventStart = false;
	switch (m_info->m_state)
	{
	case LYN_STATE_BATTLE_STANDARD:
		m_animController_lower->PlayBlending("Lyn_B_Std_Mov_Idle");
		break;
	case LYN_STATE_PEACE_STANDARD:
		m_animController_lower->PlayBlending("Lyn_P_Std_Mov_Idle");
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		break;
	default:
		break;
	}



}

void LynIdle::UpdateState()
{
	if (m_eventStart)
	{
		if (m_animController_upper->GetPlayRemainTime() < 0.3f)
		{
			m_animController_lower->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

			string anim = Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4");
			m_animController_lower->PlayBlending(anim);
		}
	}
	else
	{
		if (m_idleTime < 0.f)
		{
			m_animController_lower->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

			string anim = Nalmak_Math::Random<string>("Lyn_P_Std_Idle_Event1", "Lyn_P_Std_Idle_Event2", "Lyn_P_Std_Idle_Event3", "Lyn_P_Std_Idle_Event4");
			m_animController_lower->PlayBlending(anim);
			m_eventStart = true;
		}

		m_idleTime -= dTime;
	}





	m_lynMoveControl->UpdatePosition();

	if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_LOWER))
		return;

	LYN_MOVE_DIR_STATE state = m_lynMoveControl->GetDirectionState();
	if (state != LYN_MOVE_DIR_STATE_NONE)
	{
		SetState(L"move");
		return;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		SetState(L"jump");
		return;
	}
	
	if (!m_character->IsGround())
	{
		SetState(L"fall");
		return;
	}


	AnimationClip* lowerClip = m_animController_lower->GetCurrentPlayAnimation();
	AnimationClip* upperClip = m_animController_upper->GetCurrentPlayAnimation();

	if (lowerClip != upperClip)
	{
		double playTime = m_animController_upper->GetPlayTime();
		m_animController_lower->PlayBlending(upperClip, playTime);
	}
}

void LynIdle::ExitState()
{
	m_lynSkillControl->SetInteger(L"IsBlend",0);

}
