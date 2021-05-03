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
		m_lynControl->SetSpeed(m_info->m_runBackwardSpeed);
	}
	else
	{
		m_lynControl->SetSpeed(m_info->m_runForwardSpeed);
	}
}

void LynMove::UpdateState()
{
	if (!m_character->IsGround())
	{
		SetState(L"fall");
		return;
	}

	m_lynControl->UpdatePosition();


	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		/*m_animController_lower->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		m_charcterController->SetVelocityY(m_info->m_jumpPower);
		if (m_inputDir.x < -0.5f)
			animName = "Mov_IdleToJump_Left";
		else if (m_inputDir.x > 0.5f)
			animName = "Mov_IdleToJump_Right";
		else
			animName = "Mov_IdleToJump_Front";*/
	}

	auto lowerAnim = m_animController_lower->GetCurrentPlayAnimation();
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
	}

	m_animController_lower->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

	string animName = "";
	switch (m_lynControl->GetDirectionState())
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
		animName = "Mov_Idle";
		break;
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
		m_animController_lower->PlayBlending(animName);
	}
}

void LynMove::ExitState()
{
}
