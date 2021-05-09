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
	m_dirState = LYN_MOVE_DIR_STATE_MAX;
	PlayAnimationByDirection();
}

void LynMove::UpdateState()
{
	PlayAnimationByDirection();

	m_info->UseEnergy(-2);

	if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_info->SetSpeed(m_info->m_runForwardSpeed);
	}
	else
	{
		m_info->SetSpeed(m_info->m_runBackwardSpeed);
	}
	
	if (!m_character->IsGround())
	{
		SetState(L"fall");
		return;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		SetState(L"jump");
		return;
	}
}

void LynMove::ExitState()
{
}

void LynMove::PlayAnimationByDirection()
{
	auto dir = m_info->GetDirectionState();
	auto state = m_info->GetState();
	if (dir != m_dirState || state != m_state)
	{

		m_dirState = dir;
		string animName = "";
		switch (m_dirState)
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
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetInteger(L"IsBlend", 1);
			SetState(L"idle");
			return;
		}
		default:
			break;
		}
	
		m_state = state;
		if (animName != "")
		{
			switch (state)
			{
			case LYN_STATE_PEACE_STANDARD:
				animName = "Lyn_P_Std_" + animName;
				break;
			case LYN_STATE_BATTLE_STANDARD:
				animName = "Lyn_B_Std_" + animName;
				break;
			case LYN_STATE_BATTLE_HIDEBLADE:
				animName = "Lyn_B_Hide_" + animName;
				break;
			default:
				break;
			}
		
			/*if (GetInteger(L"IsBlend") == 2)
			{
				m_animController->PlayBlending(animName, m_animController->GetPlayTime());
			}
			else
			{
			}*/
			if (GetInteger(L"IsBlend") == 0)
				m_animController->Play(animName);
			else
				m_animController->PlayBlending(animName);

			SetInteger(L"IsBlend", 1);
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		}
		
	

	}
}
