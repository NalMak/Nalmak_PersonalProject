#include "stdafx.h"
#include "LynBaldo.h"


LynBaldo::LynBaldo()
{
}


LynBaldo::~LynBaldo()
{
}

void LynBaldo::Initialize()
{
}

void LynBaldo::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Hide_Baldo0");
	ReduceInnerPower(1);
}

void LynBaldo::UpdateState()
{

	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);
	}

	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	
}

void LynBaldo::ExitState()
{
	m_info->EndSkill();
}
