#include "stdafx.h"
#include "LynUpperSlash.h"


LynUpperSlash::LynUpperSlash()
{
}


LynUpperSlash::~LynUpperSlash()
{
}

void LynUpperSlash::Initialize()
{
}

void LynUpperSlash::EnterState()
{
	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);

	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 16.f;
		buff.key = L"F";
		buff.skill = m_skillController->GetSkill(L"upperSlash");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);
	}

	AttackInfo::Desc info;
	info.attackType = ATTACK_TYPE_AIR;
	info.ccTime = 1.5f;
	info.colliderType = COLLIDER_TYPE_BOX;
	info.depth = 10.f;
	info.height = 8.f;
	info.width = 8.f;
	CreateAttackInfo(&info, 5.f, 4.f, 0.5f);

	m_info->ChangeSkillByState(LYN_SKILL_STATE_AIR);

	m_animController->PlayBlending("Lyn_B_upperSlash2");
}

void LynUpperSlash::UpdateState()
{
	if (m_animController->IsOverTime(0.6f))
	{
		m_info->EndSkill();
	}

	if (m_animController->GetPlayRemainTime() < 0.1f)
	{
		m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynUpperSlash::ExitState()
{
	m_info->EndSkill();
}
