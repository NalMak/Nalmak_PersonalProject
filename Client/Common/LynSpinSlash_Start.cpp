#include "stdafx.h"
#include "LynSpinSlash_Start.h"


LynSpinSlash_Start::LynSpinSlash_Start()
{
}


LynSpinSlash_Start::~LynSpinSlash_Start()
{
}

void LynSpinSlash_Start::Initialize()
{
}

void LynSpinSlash_Start::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_SpinSlash_01");
	m_info->StartSkill();
	//m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,-0.5f,0 }, 0.75f, { 0,0 }, { 0.179f,0.01f }, { 0.82f,0.75f }, { 1,0 });
}

void LynSpinSlash_Start::UpdateState()
{

	if (!m_animController->IsPlay())
	{
		SetState(L"spinSlash_end");
	}
}

void LynSpinSlash_Start::ExitState()
{
	m_info->EndSkill();
}
