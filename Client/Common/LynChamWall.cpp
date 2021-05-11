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
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Chamwall");
}

void LynChamWall::UpdateState()
{
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
