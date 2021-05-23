#include "stdafx.h"
#include "LynStarAttack.h"


LynStarAttack::LynStarAttack()
{
}


LynStarAttack::~LynStarAttack()
{
}

void LynStarAttack::Initialize()
{
}

void LynStarAttack::EnterState()
{
	m_info->ChangeSkillByState(LYN_SKILL_STATE_AIR_COMBO);
	m_info->StartSkill();

	m_animController->Play("Lyn_B_takeWing");

	m_attackInfo.attackType = ATTACK_TYPE_AIR;
	m_attackInfo.ccTime = 2.f;
	m_attackInfo.colliderType = COLLIDER_TYPE_BOX;
	m_attackInfo.depth = 10.f;
	m_attackInfo.height = 8.f;
	m_attackInfo.width = 8.f;
	m_attackInfo.host = m_gameObject;
	m_target = nullptr;
	auto target = m_info->GetTarget();
	if (target)
	{
		m_target = target->GetComponent<BnS_Enemy>();
	}
}

void LynStarAttack::UpdateState()
{
	for (int i = 0; i < 5; ++i)
	{
		if (m_animController->IsOverTime(0.3f + 0.15f * i))
		{
			if (m_target)
			{
				m_attackInfo.power = (UINT)(m_info->m_power * 0.5f * Nalmak_Math::Rand(0.8f, 1.2f));
				
				float critical = Nalmak_Math::Rand(0.f, 1.f);
				m_attackInfo.isCritical = m_info->m_criticalRatio > critical;
				AttackInfo attackInfo = AttackInfo(&m_attackInfo);

				m_target->HitByAttackInfo(&attackInfo);
			}
		}
	}
	if (m_animController->IsOverTime(0.1f))
	{
		m_effect->StartWeaponTrail();
	}
	if (m_animController->IsOverTime(0.8f))
	{
		m_info->EndSkill();
	}

	if (m_animController->IsOverTime(1.f))
	{
		m_effect->EndWeaponTrail();
	}
	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		m_animController->SetBlendOption(0.5f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	else
	{
		m_info->ChangeSkillByState(LYN_SKILL_STATE_AIR_COMBO);
	}
}

void LynStarAttack::ExitState()
{

	m_info->EndSkill();
}
