#include "stdafx.h"
#include "LynLightningSlash.h"


LynLightningSlash::LynLightningSlash()
{
}


LynLightningSlash::~LynLightningSlash()
{
}

void LynLightningSlash::Initialize()
{
}

void LynLightningSlash::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_ThunderCut");
	m_info->StartSkill();
}

void LynLightningSlash::UpdateState()
{
	if (m_animController->IsOverTime(0.3))
	{
		m_info->SetSpeed(m_info->m_runForwardSpeed * 0.5f);
	}
	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_info->SetState(LYN_STATE_BATTLE_HIDEBLADE);
		m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_LINEAR);
		SetInteger(L"IsBlend", 1);
		SetState(L"idle");
		return;
	}
}

void LynLightningSlash::ExitState()
{
	m_info->SetSpeed(m_info->m_runForwardSpeed);
	m_info->EndSkill();
}
