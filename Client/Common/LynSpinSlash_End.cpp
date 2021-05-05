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
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_SpinSlash_02");
}

void LynSpinSlash_End::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 1.f)
	{
		SetState(L"idle");
		return;
	}
}

void LynSpinSlash_End::ExitState()
{
	SetInteger(L"IsBlend", 0);
	m_info->EndSkill();
}
