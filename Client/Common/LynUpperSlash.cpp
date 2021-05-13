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

	AttackInfo::Desc info;
	info.attackType = ATTACK_TYPE_AIR;
	info.ccTime = 2.f;
	info.colliderType = COLLIDER_TYPE_BOX;
	info.depth = 4.f;
	info.height = 5.f;
	info.width = 5.f;
	CreateAttackInfo(&info, 3.f, 2.f, 0.5f);

	m_animController->Play("Lyn_B_upperSlash2");
}

void LynUpperSlash::UpdateState()
{
	
	if (!m_animController->IsPlay())
	{
		SetState(L"idle");
		return;
	}
}

void LynUpperSlash::ExitState()
{
	m_info->EndSkill();
}
