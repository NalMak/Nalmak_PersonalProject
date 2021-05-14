#include "stdafx.h"
#include "LynLightningCombo.h"


LynLightningCombo::LynLightningCombo()
{
}


LynLightningCombo::~LynLightningCombo()
{
}

void LynLightningCombo::Initialize()
{

}

void LynLightningCombo::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);
	m_animController->Play("Lyn_B_Hide_LightningCombo");
}

void LynLightningCombo::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}


}

void LynLightningCombo::ExitState()
{
	m_info->EndSkill();
}
