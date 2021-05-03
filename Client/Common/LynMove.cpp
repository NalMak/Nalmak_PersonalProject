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
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];


	m_moveState = LYN_MOVE_STATE_RUN;
	m_inputDir = { 0,0,0 };

	//m_animController_upper->Play("Lyn_P_Std_Mov_RunFront");
	//m_animController_upper->SetActive(false);
	//m_animController_lower->Play("Lyn_P_Std_Mov_RunFront");
	//m_animController_lower->Play("Lyn_P_Std_Mov_RunFront");


}

void LynMove::Update()
{
	m_info->UpdateWeapon();

	string animName = "";

	UpdateMoveState();
	UpdateDirectionByKey();
	m_inputDir = Nalmak_Math::Lerp(m_inputDir, m_targetInput, dTime * 10);

	
	
	////////////////////////////////////////////////////////////// 현재 방향 갱신
	LYN_MOVE_DIR_STATE moveDirState = LYN_MOVE_DIR_STATE_NONE;
	float shortLength = INFINITY;
	int index = 0;
	for (int i = 0; i < 9; ++i)
	{
		float length = Nalmak_Math::DistanceSq(m_directionState[i], m_inputDir);
		if (length < shortLength)
		{
			index = i;
			shortLength = length;
		}
	}
	moveDirState = (LYN_MOVE_DIR_STATE)index;
	DEBUG_LOG(L"moveDir", moveDirState);

	////////////////////////////////////////////////////////////// 현재 속도 갱신

	float targetSpeed = 0;
	switch (m_moveState)
	{
	case LynMove::LYN_MOVE_STATE_IDLE:
		targetSpeed = 0;
		break;
	case LynMove::LYN_MOVE_STATE_RUN:
		if(moveDirState == LYN_MOVE_DIR_STATE_BACK || moveDirState == LYN_MOVE_DIR_STATE_BACKRIGHT || moveDirState == LYN_MOVE_DIR_STATE_BACKLEFT)
			targetSpeed = m_info->m_runBackwardSpeed;
		else
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
	if(m_moveState == LYN_MOVE_STATE_JUMP)
		m_charcterController->AddVelocity(0, -30.f * dTime, 0);
	////////////////////////////////////////////////////////////// 상하체 다를 시 조건

	auto lowerAnim = m_animController_lower->GetCurrentPlayAnimation();
	auto upperAnim = m_animController_upper->GetCurrentPlayAnimation();


	if (lowerAnim != upperAnim)
	{
		
		if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_UPPER))
		{
			if (moveDirState == LYN_MOVE_DIR_STATE_NONE)
			{
				if (m_moveState != LYN_MOVE_STATE_JUMP)
				{
					m_animController_lower->PlayBlending(upperAnim);
					return;
				}
			}
		}
		else
			m_animController_upper->PlayBlending(lowerAnim);
	}
	
	////////////////////////////////////////////////////////////// 점프 시 조건
	if (m_moveState != LYN_MOVE_STATE_JUMP)
	{
		if(m_preState == LYN_MOVE_STATE_JUMP)
		{
			switch (moveDirState)
			{
			case LynMove::LYN_MOVE_DIR_STATE_FRONT:
				animName = "Mov_JumpToMove_Front";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACK:
				animName = "Mov_JumpToMove_Back";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTLEFT:
			case LynMove::LYN_MOVE_DIR_STATE_LEFT:
				animName = "Mov_JumpToMove_Left";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTRIGHT:
			case LynMove::LYN_MOVE_DIR_STATE_RIGHT:
				animName = "Mov_JumpToMove_Right";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_NONE:
				animName = "Mov_JumpToIdle";
				break;

			}
		}
		else
		{
			m_animController_lower->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

			switch (moveDirState)
			{
			case LynMove::LYN_MOVE_DIR_STATE_FRONT:
				animName = "Mov_RunFront";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_RIGHT:
				animName = "Mov_RunRight";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTRIGHT:
				animName = "Mov_RunRightFront";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_LEFT:
				animName = "Mov_RunLeft";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_FRONTLEFT:
				animName = "Mov_RunLeftFront";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACK:
				animName = "Mov_RunBack";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACKRIGHT:
				animName = "Mov_RunRightBack";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_BACKLEFT:
				animName = "Mov_RunLeftBack";
				break;
			case LynMove::LYN_MOVE_DIR_STATE_NONE:
				animName = "Mov_Idle";
				break;
			default:
				break;
			}

			if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
			{
				m_animController_lower->SetBlendOption(0.15f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
				m_charcterController->SetVelocityY(m_info->m_jumpPower);
				if (m_inputDir.x < -0.5f)
					animName = "Mov_IdleToJump_Left";
				else if (m_inputDir.x > 0.5f)
					animName = "Mov_IdleToJump_Right";
				else
					animName = "Mov_IdleToJump_Front";
			}
		}
	}
	else
	{
		
		if (m_animController_lower->GetPlayRemainTime() < 0.1f)
		{
			m_animController_lower->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		}
		
		
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

void LynMove::UpdateMoveState()
{
	m_preState = m_moveState;
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
