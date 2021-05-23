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
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_info->SetBattleState(BATTLE_STATE_DOWN);
	m_info->ChangeSkillByState(LYN_SKILL_STATE_LAY);


	m_animController->PlayBlending("Lyn_B_Down");
	m_bnsMainCam->UnLockTarget();

	m_downTimer = GetFloat(L"downTime");

	m_character->SetVelocityXZ(Vector3(0, 0, 0));
	m_backRollTimer = 1.f;
}

void LynLayDown::UpdateState()
{
	if (m_backRollTimer > 0)
	{
		m_backRollTimer -= dTime;
	}
	else
	{
		m_skillController->ReleaseSkill(BNS_SKILL_SLOT_F);
	}

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
	if (m_isUpper)
	{
		m_info->SetSpeed(m_info->m_runForwardSpeed);
		m_bnsMainCam->LockTarget();

		m_skillController->ReleaseSkill(BNS_SKILL_SLOT_F);
		m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
	}

}
