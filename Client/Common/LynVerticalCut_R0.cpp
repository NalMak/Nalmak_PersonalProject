#include "stdafx.h"
#include "LynVerticalCut_R0.h"


LynVerticalCut_R0::LynVerticalCut_R0()
{
}


LynVerticalCut_R0::~LynVerticalCut_R0()
{
}

void LynVerticalCut_R0::Initialize()
{
}

void LynVerticalCut_R0::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_02_1");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


}

void LynVerticalCut_R0::UpdateState()
{
	if (!m_animController_upper->IsPlay())
	{
		SetState(L"verticalCut_r1");
	}
}

void LynVerticalCut_R0::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);


}
