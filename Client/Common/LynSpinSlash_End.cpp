#include "stdafx.h"
#include "LynSpinSlash_End.h"


LynSpinSlash_End::LynSpinSlash_End()
{
}


LynSpinSlash_End::~LynSpinSlash_End()
{
}

void LynSpinSlash_End::Initialize()
{
}

void LynSpinSlash_End::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_SpinSlash_02");

	m_info->SetSpeed(m_info->m_airSpeed);
}

void LynSpinSlash_End::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 1.2f)
	{
		m_animController->SetBlendOption(0.5f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynSpinSlash_End::ExitState()
{
	m_info->SetBattleState(BATTLE_STATE_WEAK);
	m_info->EndSkill();
}
