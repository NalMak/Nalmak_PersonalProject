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
