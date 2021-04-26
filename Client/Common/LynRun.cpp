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
		SetState(L"idle");
		return;
	}

	if (m_preDirection != m_moveDirection)
	{
		UpdateAnimState();
	}

	m_preDirection = m_moveDirection;
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_SPACE))
	{
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
		velocity += { 0,0,1 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_LEFT;
		velocity += { -1, 0, 0 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_DOWN;
		velocity += { 0, 0, -1 };
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		moveDir += LynRun::MOVE_DIRECTION::MOVE_DIRECTION_RIGHT;
		velocity += { 1, 0, 0 };
	}

	velocity = Nalmak_Math::Normalize(velocity);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_character->SetVelocity(velocity * m_info->m_runBackwardSpeed);
	}
	else
	{
		m_character->SetVelocity(velocity * m_info->m_runForwardSpeed);
	}


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
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_LEFT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunLeft";
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_RIGHT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunRight";
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_UP)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunFront";
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_DOWN + MOVE_DIRECTION_LEFT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunLeftBack";
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_DOWN + MOVE_DIRECTION_RIGHT)
	{
		nextAnimName = "Lyn_P_Std_Mov_RunRightBack";
		m_animController->Play(nextAnimName, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_UP + MOVE_DIRECTION_LEFT)
	{
		m_animController->Play("Lyn_P_Std_Mov_RunFront", "Lyn_P_Std_Mov_RunLeft",0.5f, 0.1f, 1.f);
	}
	else if (m_moveDirection == MOVE_DIRECTION_UP + MOVE_DIRECTION_RIGHT)
	{
		m_animController->Play("Lyn_P_Std_Mov_RunFront", "Lyn_P_Std_Mov_RunRight", 0.5f, 0.1f, 1.f);
	}
		
}
