#include "stdafx.h"
#include "LynFrontKick.h"


LynFrontKick::LynFrontKick()
{
}


LynFrontKick::~LynFrontKick()
{
}

void LynFrontKick::Initialize()
{
}

void LynFrontKick::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_FrontKick");

	
}

void LynFrontKick::UpdateState()
{
	
	if (m_animController->IsOverTime(0.3f))
	{
		AttackInfo::Desc info;
		info.attackType = ATTACK_TYPE_DOWN;
		info.ccTime = 2.f;
		info.colliderType = COLLIDER_TYPE_BOX;
		info.depth = 4.f;
		info.height = 5.f;
		info.width = 3.f;
		CreateAttackInfo(&info, 3.f, 2.f, 0.3f);
	}

	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynFrontKick::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
}
