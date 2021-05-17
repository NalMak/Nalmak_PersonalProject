#include "stdafx.h"
#include "LynExcape.h"


LynExcape::LynExcape()
{
}


LynExcape::~LynExcape()
{
}

void LynExcape::Initialize()
{
}

void LynExcape::EnterState()
{
	m_info->SetResistance(true);

	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_info->SetBattleState(BATTLE_STATE_RESISTANCE);

	m_animController->Play("Lyb_B_Std_Excape_1");

	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 30.f;
		buff.key = L"Tab";
		buff.skill = m_skillController->GetSkill(L"excape");
		auto soulBlade = INSTANTIATE()->AddComponent<BnS_Buff>(&buff);
	}
}

void LynExcape::UpdateState()
{
	if (!m_animController->IsPlay("Lyb_B_Std_Excape_1"))
	{
		m_animController->Play("Lyb_B_Std_Excape_2");
	}
	if (m_animController->GetCurrentPlayAnimationName() == "Lyb_B_Std_Excape_2")
	{
		if (m_animController->GetPlayRemainTime() < 0.6f)
		{
			SetState(L"idle");
			m_animController->SetBlendOption(0.6f, 1.f, D3DXTRANSITION_LINEAR);
			return;
		}
	}
	
}

void LynExcape::ExitState()
{
	m_info->SetResistance(false);
	m_info->SetResistanceTimer(1.f);
	m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);


	m_info->EndSkill();
}
