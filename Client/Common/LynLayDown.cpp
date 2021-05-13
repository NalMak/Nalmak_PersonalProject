#include "stdafx.h"
#include "LynLayDown.h"


LynLayDown::LynLayDown()
{
}


LynLayDown::~LynLayDown()
{
}

void LynLayDown::Initialize()
{
	
}

void LynLayDown::EnterState()
{
	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Down");
	m_bnsMainCam->UnLockTarget();

	m_downTimer = GetFloat(L"downTime");

	m_character->SetVelocityXZ(Vector3(0, 0, 0));
}

void LynLayDown::UpdateState()
{
	if (m_downTimer > 0)
	{
		m_downTimer -= dTime;
	}
	else
	{
		SetState(L"wakeUp");
		return;
	}
}

void LynLayDown::ExitState()
{
	m_info->SetSpeed(m_info->m_runForwardSpeed);
	m_info->EndSkill();
	m_bnsMainCam->LockTarget();
}
