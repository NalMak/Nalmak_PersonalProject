#include "stdafx.h"
#include "LynSpinSlash_Combo.h"


LynSpinSlash_Combo::LynSpinSlash_Combo()
{
}

LynSpinSlash_Combo::~LynSpinSlash_Combo()
{
}

void LynSpinSlash_Combo::Initialize()
{
}

void LynSpinSlash_Combo::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_SpinSlash_01_1");
	m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,3.5f,0 }, 0.75f, { 0,0 }, { 0.179f,0.01f }, { 0.82f,0.75f }, { 1,0 });

}

void LynSpinSlash_Combo::UpdateState()
{
	if (!m_animController->IsPlay())
	{
		SetState(L"spinSlash_end");
		return;
	}
}

void LynSpinSlash_Combo::ExitState()
{
	SetInteger(L"IsBlend", 0);
	m_info->EndSkill();
}
