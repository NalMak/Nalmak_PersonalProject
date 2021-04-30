#include "stdafx.h"
#include "LynMove.h"
#include "LynInfo.h"


LynMove::LynMove(Desc * _desc)
{
}

LynMove::~LynMove()
{
}

void LynMove::Initialize()
{
	m_info = GetComponent<LynInfo>();
	m_charcterController = GetComponent<CharacterController>();
	m_animController = GetComponent<AnimationController>();

	m_moveState = LYN_MOVE_STATE_RUN;
	m_moveDirState = LYN_MOVE_DIR_STATE_NONE;
	m_inputDir = { 0,0,0 };

	m_animController->Play("Lyn_P_Std_Mov_RunFront");

}

void LynMove::Update()
{
	UpdateMoveState();
	UpdateDirectionByKey();
	m_inputDir = Nalmak_Math::Lerp(m_inputDir, m_targetInput, dTime * 10);

	float targetSpeed = 0;
	switch (m_moveState)
	{
	case LynMove::LYN_MOVE_STATE_IDLE:
		targetSpeed = 0;
		break;
	case LynMove::LYN_MOVE_STATE_RUN:
		targetSpeed = m_info->m_runForwardSpeed;
		break;
	case LynMove::LYN_MOVE_STATE_JUMP:
		targetSpeed = m_info->m_airSpeed;
		break;
	}

	Vector3 velocity = { 0,0,0 };
	velocity += m_inputDir.x * m_transform->GetRight() * targetSpeed;
	velocity += m_inputDir.z * m_transform->GetForward() * targetSpeed;

	m_charcterController->SetVelocityX(velocity.x);
	m_charcterController->SetVelocityZ(velocity.z);

	LYN_MOVE_DIR_STATE moveDirState = LYN_MOVE_DIR_STATE_NONE;

	if (m_moveState != LYN_MOVE_STATE_JUMP)
	{
		if (m_targetInput == Vector3(0, 0, 0))
		{
			moveDirState = LYN_MOVE_DIR_STATE_NONE;
		}
		else
		{
			float shortLength = INFINITY;
			int index = 0;
			for (int i = 0; i < 10; ++i)
			{
				float length = Nalmak_Math::DistanceSq(m_directionState[i], m_inputDir);
				if (length < shortLength)
				{
					index = i;
					shortLength = length;
				}
			}
			moveDirState = (LYN_MOVE_DIR_STATE)index;
		}
		if (m_moveDirState != moveDirState)
		{
			m_animController->SetBlendOption(0.2f, 0.8f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

			switch (moveDirState)
			{
			case LynMove::LYN_MOVE_DIR_STATE_FRONT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunFront");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_RIGHT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunRight");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTRIGHT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunRightFront");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_LEFT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunLeft");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTLEFT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunLeftFront");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACK:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunBack");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACKRIGHT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunRightBack");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACKLEFT:
				m_animController->PlayBlending("Lyn_P_Std_Mov_RunLeftBack");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_NONE:
				m_animController->PlayBlending("Lyn_P_Std_Idle_Event1");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_LEFTTORIGHT:
				m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
				m_animController->PlayBlending("Lyn_P_Std_Mov_LeftToRight");
				break;
			case LynMove::LYN_MOVE_DIR_STATE_RIGHTTOLEFT:
				m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
				m_animController->PlayBlending("Lyn_P_Std_Mov_RightToLeft");
				break;
			default:
				break;
			}
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
		{
			m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			m_charcterController->SetVelocityY(m_info->m_jumpPower);
			if(m_inputDir.x < -0.5f)
				m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Left");
			else if(m_inputDir.x > 0.5f)
				m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Right");
			else
				m_animController->PlayBlending("Lyn_P_Std_Mov_IdleToJump_Front");
		}
	}
	else
	{
		
		if (m_animController->GetPlayRemainTime() < 0.1f)
		{
			m_animController->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			if (m_inputDir.x < -0.5f)
				m_animController->PlayBlending("Lyn_P_Std_Mov_JumpLeft");
			else if (m_inputDir.x > 0.5f)
				m_animController->PlayBlending("Lyn_P_Std_Mov_JumpRight");
			else
				m_animController->PlayBlending("Lyn_P_Std_Mov_JumpFront");
		}
		
		m_charcterController->AddVelocity(0, -30.f * dTime, 0);
	}
	m_moveDirState = moveDirState;
	
}

void LynMove::UpdateMoveState()
{
	if (!m_charcterController->IsGround())
	{
		m_moveState = LYN_MOVE_STATE_JUMP;
	}
	else
	{
		if (m_targetInput == 0)
		{
			m_moveState = LYN_MOVE_STATE_IDLE;
		}
		else
		{
			m_moveState = LYN_MOVE_STATE_RUN;
		}
	}
}

void LynMove::UpdateDirectionByKey()
{
	m_targetInput = { 0,0,0 };
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_targetInput += {0, 0, 1};
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_targetInput -= {0, 0, 1};
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_targetInput -= {1, 0, 0};
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_targetInput += {1, 0, 0};
	}
	m_targetInput = Nalmak_Math::Normalize(m_targetInput);

}
