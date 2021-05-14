#include "stdafx.h"
#include "LynDead.h"
#include "BnS_Enemy.h"


LynDead::LynDead()
{
}


LynDead::~LynDead()
{
}

void LynDead::Initialize()
{
}

void LynDead::EnterState()
{
	m_bnsMainCam->UnLockTarget();
	m_info->SetState(LYN_STATE_PEACE_STANDARD);
	m_info->SetSpeed(0.f);
	m_info->StartSkill();
	m_info->SetBattleState(BATTLE_STATE_DEAD);
	m_animController->PlayBlending("Lyn_B_Dead");
}

void LynDead::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Dead")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Exhausted_Mov_Idle");
		}
	}
}

void LynDead::ExitState()
{
	m_bnsMainCam->LockTarget();
	m_info->EndSkill();
}
