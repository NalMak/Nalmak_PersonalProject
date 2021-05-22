#include "stdafx.h"
#include "LynSlash2.h"


LynSlash2::LynSlash2()
{
}

LynSlash2::~LynSlash2()
{
}

void LynSlash2::Initialize()
{
	m_slash3Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon02");
	m_slash1Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon00");

}

void LynSlash2::EnterState()
{
	ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash3Tex, L"��ǳ");

	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash2");



	m_isCombo = false;


	PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_slash2_2", L"lyn_slash2_3"));

}

void LynSlash2::UpdateState()
{
	if (m_animController->IsOverTime(0.15f))
	{
		AttackInfo::Desc attack;
		attack.height = 5;
		attack.depth = 10;
		attack.width = 8;
		attack.innerPower = 1;
		CreateAttackInfo(&attack, 5.f, 1.5f, 1.f);

		m_effect->StartWeaponTrail();
	}

	if (BETWEEN(m_animController->GetPlayRemainTime(), 0.8f, 1.2f))
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	

	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.8f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash3");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.6f)
		{
			m_animController->SetBlendOption(0.6f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash2::ExitState()
{
	if(!m_isCombo)
		ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex, L"��ǳ");

	m_effect->EndWeaponTrail();

	m_info->EndSkill();
}
