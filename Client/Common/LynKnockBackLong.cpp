#include "stdafx.h"
#include "LynKnockBackLong.h"


LynKnockBackLong::LynKnockBackLong()
{
}


LynKnockBackLong::~LynKnockBackLong()
{
}

void LynKnockBackLong::Initialize()
{
}

void LynKnockBackLong::EnterState()
{


	m_info->StartSkill();
	m_info->SetSpeed(0);
	m_info->MoveOn();
	m_bnsMainCam->UnLockTarget();
	m_info->ChangeSkillByState(LYN_SKILL_STATE_CC);
	m_info->SetBattleState(BATTLE_STATE_KNOCKBACK);

	m_character->SetVelocity(0, 20, 0);
	m_animController->Play("Lyn_B_KnockBack_Long_B");
}

void LynKnockBackLong::UpdateState()
{
	if (m_animController->GetPlayRatio() > 0.1f)
	{
		if (m_character->IsGround())
		{
			m_character->SetVelocityXZ(Vector3(0, 0, 0));
			SetState(L"down");
			return;
		}
	}
}

void LynKnockBackLong::ExitState()
{
	m_info->EndSkill();
	m_info->MoveOff();

	m_bnsMainCam->LockTarget();
}
