#include "stdafx.h"
#include "LynWakeUp.h"


LynWakeUp::LynWakeUp()
{
}


LynWakeUp::~LynWakeUp()
{
}

void LynWakeUp::Initialize()
{
}

void LynWakeUp::EnterState()
{
	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->SetBattleState(BATTLE_STATE_RESISTANCE);
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_wakeUp2");
	m_bnsMainCam->UnLockTarget();
}

void LynWakeUp::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynWakeUp::ExitState()
{
	m_info->SetSpeed(m_info->m_runForwardSpeed);
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
	m_bnsMainCam->LockTarget();
}
