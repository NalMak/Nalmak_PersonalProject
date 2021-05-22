#include "stdafx.h"
#include "LynChamWall.h"


LynChamWall::LynChamWall()
{
}


LynChamWall::~LynChamWall()
{
}

void LynChamWall::Initialize()
{
}

void LynChamWall::EnterState()
{
	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 8.f;
		buff.key = L"";
		buff.skill = m_skillController->GetSkill(L"atkBuff");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);

	}

	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Chamwall");

	PlayOneShot(L"SoulSword_Lightning_Hit04");
}

void LynChamWall::UpdateState()
{
	if (m_animController->IsOverTime(0.1f))
	{
		AttackInfo::Desc attack;
		attack.depth = 8.f;
		attack.height = 8.f;
		attack.width = 8.f;
		CreateAttackInfo(&attack, 4.f, 4.f, 10.f);
	}
	if (m_animController->IsOverTime(0.2f))
	{
		AttackInfo::Desc attack;
		attack.depth = 8.f;
		attack.height = 8.f;
		attack.width = 8.f;
		CreateAttackInfo(&attack, 4.f, 4.f, 10.f);
	}
	if (m_animController->IsOverTime(0.3f))
	{
		AttackInfo::Desc attack;
		attack.depth = 8.f;
		attack.height = 8.f;
		attack.width = 8.f;
		CreateAttackInfo(&attack, 4.f, 4.f, 10.f);
	}
	if (m_animController->IsOverTime(0.4f))
	{
		AttackInfo::Desc attack;
		attack.depth = 8.f;
		attack.height = 8.f;
		attack.width = 8.f;
		CreateAttackInfo(&attack, 4.f, 4.f, 10.f);
	}
	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynChamWall::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_HIDEBLADE);

}
