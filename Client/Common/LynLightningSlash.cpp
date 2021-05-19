#include "stdafx.h"
#include "LynLightningSlash.h"


LynLightningSlash::LynLightningSlash()
{
}


LynLightningSlash::~LynLightningSlash()
{
}

void LynLightningSlash::Initialize()
{
}

void LynLightningSlash::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_ThunderCut");
	m_info->StartSkill();

	PlayOneShot(L"BladeMaster_G3_Mach_Slash_Lv1_Fire_01");

	AttackInfo::Desc attack;
	attack.height = 5;
	attack.depth = 5;
	attack.width = 8;
	attack.soundName = L"Fencer_MachSlash_Hit";
	CreateAttackInfo(&attack, 3.f, 1.5f, 4.f);
}

void LynLightningSlash::UpdateState()
{
	if (m_animController->IsOverTime(0.3))
	{
		m_info->SetSpeed(m_info->m_runForwardSpeed * 0.5f);
	}
	if (m_animController->GetPlayRemainTime() < 0.6f)
	{
		m_animController->SetBlendOption(0.6f, 1.f, D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynLightningSlash::ExitState()
{
	m_info->SetState(LYN_STATE_BATTLE_HIDEBLADE);
	m_info->SetSpeed(m_info->m_runForwardSpeed);
	m_info->EndSkill();
}
