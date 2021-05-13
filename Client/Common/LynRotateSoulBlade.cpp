#include "stdafx.h"
#include "LynRotateSoulBlade.h"


LynRotateSoulBlade::LynRotateSoulBlade()
{
}


LynRotateSoulBlade::~LynRotateSoulBlade()
{
}

void LynRotateSoulBlade::Initialize()
{
}

void LynRotateSoulBlade::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(0);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Hide_RotateSoulBlade");
}

void LynRotateSoulBlade::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynRotateSoulBlade::ExitState()
{
}
