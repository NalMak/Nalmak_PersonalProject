#include "stdafx.h"
#include "LynLowerSlash2.h"


LynLowerSlash2::LynLowerSlash2()
{
}


LynLowerSlash2::~LynLowerSlash2()
{
}

void LynLowerSlash2::Initialize()
{
}

void LynLowerSlash2::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_lowerSlash2");

	AttackInfo::Desc attack;
	attack.height = 7;
	attack.depth = 10;
	attack.width = 8;
	attack.attackType = ATTACK_TYPE_DOWN;
	CreateAttackInfo(&attack, 6.f, 1.5f, 1.f);
}

void LynLowerSlash2::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynLowerSlash2::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
}
