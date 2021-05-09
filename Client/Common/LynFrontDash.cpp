#include "stdafx.h"
#include "LynFrontDash.h"


LynFrontDash::LynFrontDash()
{
}


LynFrontDash::~LynFrontDash()
{
}

void LynFrontDash::Initialize()
{
}

void LynFrontDash::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_Dash_1");
}

void LynFrontDash::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		SetInteger(L"IsBlend", 1);
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynFrontDash::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
}
