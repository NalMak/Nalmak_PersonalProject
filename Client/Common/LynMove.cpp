#include "stdafx.h"
#include "LynMove.h"


LynMove::LynMove()
{
}


LynMove::~LynMove()
{
}

void LynMove::Initialize()
{
}

void LynMove::EnterState()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_lynMoveControl->SetSpeed(m_info->m_runBackwardSpeed);
	}
	else
	{
		m_lynMoveControl->SetSpeed(m_info->m_runForwardSpeed);
	}
}

void LynMove::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
		m_lynMoveControl->SetSpeed(m_info->m_runBackwardSpeed);
	else
		m_lynMoveControl->SetSpeed(m_info->m_runForwardSpeed);

	m_lynMoveControl->UpdatePosition();

	if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_LOWER))
		return;

	

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

	/*auto lowerAnim = m_animController_lower->GetCurrentPlayAnimation();
	auto upperAnim = m_animController_upper->GetCurrentPlayAnimation();

	if (lowerAnim != upperAnim)
	{
		if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_UPPER))
		{
			if (m_lynControl->GetDirectionState() == LYN_MOVE_DIR_STATE_NONE)
			{
				m_animController_lower->PlayBlending(upperAnim);
				return;
			}
		}
		else
			m_animController_upper->PlayBlending(lowerAnim);
	}*/

	

	string animName = "";
	switch (m_lynMoveControl->GetDirectionState())
	{
	case LYN_MOVE_DIR_STATE_FRONT:
		animName = "Mov_RunFront";
		break;
	case LYN_MOVE_DIR_STATE_RIGHT:
		animName = "Mov_RunRight";
		break;
	case LYN_MOVE_DIR_STATE_FRONTRIGHT:
		animName = "Mov_RunRightFront";
		break;
	case LYN_MOVE_DIR_STATE_LEFT:
		animName = "Mov_RunLeft";
		break;
	case LYN_MOVE_DIR_STATE_FRONTLEFT:
		animName = "Mov_RunLeftFront";
		break;
	case LYN_MOVE_DIR_STATE_BACK:
		animName = "Mov_RunBack";
		break;
	case LYN_MOVE_DIR_STATE_BACKRIGHT:
		animName = "Mov_RunRightBack";
		break;
	case LYN_MOVE_DIR_STATE_BACKLEFT:
		animName = "Mov_RunLeftBack";
		break;
	case LYN_MOVE_DIR_STATE_NONE:
		m_animController_lower->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
		
	default:
		break;
	}

	

	if (animName == "")
		return;

	if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_LOWER) && m_info->m_animFixPart.Check(ANIMATION_FIX_PART_UPPER))
		return;

	switch (m_info->m_state)
	{
	case LYN_STATE::LYN_STATE_PEACE_STANDARD:
		animName = "Lyn_P_Std_" + animName;
		break;
	case LYN_STATE::LYN_STATE_BATTLE_STANDARD:
		animName = "Lyn_B_Std_" + animName;
		break;
	case LYN_STATE::LYN_STATE_BATTLE_HIDEBLADE:
		break;
	default:
		break;
	}

	if (m_animController_lower->GetCurrentPlayAnimationName() != animName)
	{
		m_animController_lower->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

		m_animController_lower->PlayBlending(animName);
		if (!m_info->m_animFixPart.Check(ANIMATION_FIX_PART_UPPER))
		{
			m_animController_upper->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			m_lynSkillControl->SetInteger(L"IsBlend", 1);
			m_animController_upper->PlayBlending(animName);

		}
	}
}

void LynMove::ExitState()
{
}
