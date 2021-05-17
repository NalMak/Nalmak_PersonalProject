#include "stdafx.h"
#include "LynSlash1.h"


LynSlash1::LynSlash1()
{
}


LynSlash1::~LynSlash1()
{
}

void LynSlash1::Initialize()
{
	m_slash2Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon01");
	m_slash1Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon00");

}

void LynSlash1::EnterState()
{
	ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash2Tex);

	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash1");

	m_isCombo = false;

	AttackInfo::Desc attack;
	attack.height = 5;
	attack.depth = 5;
	attack.width = 8;
	attack.innerPower = 1;
	CreateAttackInfo(&attack, 3.f, 1.5f, 1.f);

	if (m_isUpper)
	{
		m_audio->PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_slash1_1", L"lyn_slash1_2", L"lyn_slash1_3"));
	}

}

void LynSlash1::UpdateState()
{
	
	if (BETWEEN(m_animController->GetPlayRemainTime(),0.8f,1.2f))
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
			SetState(L"slash2");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.8f)
		{
			m_animController->SetBlendOption(0.8f, 1.f, D3DXTRANSITION_FORCE_DWORD);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash1::ExitState()
{
	if (!m_isCombo)
		ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex);

	m_info->EndSkill();
}
