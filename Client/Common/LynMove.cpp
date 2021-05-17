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
	m_soundInterval = 0;
}

void LynMove::UpdateState()
{
	if (!m_isUpper)
	{
		m_soundInterval += dTime;
		float interval;
		switch (m_info->GetState())
		{
		case LYN_STATE_PEACE_STANDARD:
			interval = 0.32f;
			break;
		case LYN_STATE_BATTLE_STANDARD:
			interval = 0.295f;
		case LYN_STATE_BATTLE_HIDEBLADE:
			interval = 0.29f;
		default:
			break;
		}
		if (m_soundInterval >interval)
		{
			wstring source = Nalmak_Math::Random<wstring>(L"lyn_move1", L"lyn_move2", L"lyn_move3", L"lyn_move4", L"lyn_move5", L"lyn_move6");
			m_audio->PlayOneShot(source);
			m_soundInterval -= interval;
		}
	}
	


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
		string animName = "";
		switch (dir)
		{
		case LYN_MOVE_DIR_STATE_FRONT:
			animName = "Mov_RunFront";
			break;
		case LYN_MOVE_DIR_STATE_RIGHT:
		{
			if (m_dirState == LYN_MOVE_DIR_STATE_LEFT)
			{
				SetState(L"rebound");
				m_dirState = dir;
				return;
			}
			else
			{
				animName = "Mov_RunRight";
				break;
			}
		}
		case LYN_MOVE_DIR_STATE_FRONTRIGHT:
			animName = "Mov_RunRightFront";
			break;
		case LYN_MOVE_DIR_STATE_LEFT:
		{
			if (m_dirState == LYN_MOVE_DIR_STATE_RIGHT)
			{
				SetState(L"rebound");
				m_dirState = dir;
				return;
			}
			else
			{
				animName = "Mov_RunLeft";
				break;
			}
		}
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
			if (!m_info->IsProgressingSkill())
			{
				if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_A) && !InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
				{
					m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
					SetState(L"idle");
					m_dirState = dir;
					return;
				}
			}
			else
			{
				/*if (!m_isUpper)
				{
					if (m_animController->GetCurrentPlayAnimation() != m_info->GetUpperAnimationController()->GetCurrentPlayAnimation())
					{
						SetState()
					}
				}*/
			}
		}
		default:
			break;
		}
		m_dirState = dir;
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

		
			m_animController->PlayBlending(animName);
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		}
		
	

	}
}
