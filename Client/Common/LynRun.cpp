#include "stdafx.h"
#include "LynRun.h"


LynRun::LynRun()
{
}


LynRun::~LynRun()
{
}

void LynRun::Initialize()
{
}

void LynRun::EnterState()
{
	m_moveDirection = 0;
	m_preDirection = 0;

	m_moveDirection = CalcKeyState();
	UpdateAnimState();
}

void LynRun::UpdateState()
{
	m_moveDirection = CalcKeyState();


	if (m_moveDirection == 0)
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}

	if (m_preDirection != m_moveDirection)
	{
		UpdateAnimState();
		DEBUG_LOG(L"Change run", L"");
	}

	m_preDirection = m_moveDirection;
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_SPACE))
	{
		m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idleToJump");
		return;
	}
}

void LynRun::ExitState()
{
}

UINT LynRun::CalcKeyState()
{
	UINT moveDir = 0;
	Vector3 velocity = { 0, 0, 0 };
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_UP;
		velocity += m_transform->GetForward();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_LEFT;
		velocity -= m_transform->GetRight();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_DOWN;
		velocity -= m_transform->GetForward();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_RIGHT;
		velocity += m_transform->GetRight();
	}

	if (moveDir == 0)
		return moveDir;

	velocity = Nalmak_Math::Normalize(velocity);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		velocity *= m_info->m_runBackwardSpeed;
	}
	else
	{
		velocity *= m_info->m_runForwardSpeed;
	}
	m_character->SetVelocityX(velocity.x);
	m_character->SetVelocityZ(velocity.z);



	return moveDir;
}

void LynRun::UpdateAnimState()
{
	if ((m_preDirection & MOVE_DIRECTION_LEFT && m_moveDirection & MOVE_DIRECTION_RIGHT) ||
		 (m_preDirection & MOVE_DIRECTION_RIGHT && m_moveDirection & MOVE_DIRECTION_LEFT))
	{
		SetState(L"turning");
		return;
	}

	string nextAnimName = "";
	if (m_moveDirection == MOVE_DIRECTION_DOWN)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunBack";
	}
	else if (m_moveDirection == MOVE_DIRECTION_LEFT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunLeft";
	}
	else if (m_moveDirection == MOVE_DIRECTION_RIGHT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunRight";
	}
	else if (m_moveDirection == MOVE_DIRECTION_UP)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunFront";
	}
	else if (m_moveDirection == MOVE_DIRECTION_DOWN + MOVE_DIRECTION_LEFT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunLeftBack";
	}
	else if (m_moveDirection == MOVE_DIRECTION_DOWN + MOVE_DIRECTION_RIGHT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunRightBack";
	}
	else if (m_moveDirection == MOVE_DIRECTION_UP + MOVE_DIRECTION_LEFT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunLeftFront";

	}
	else if (m_moveDirection == MOVE_DIRECTION_UP + MOVE_DIRECTION_RIGHT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunRightFront";

	}
	if (nextAnimName != "")
	{
		m_animController->SetBlendOption(0.7f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		m_animController->PlayBlending(nextAnimName);
	}
}
