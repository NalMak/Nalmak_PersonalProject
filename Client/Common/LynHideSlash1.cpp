#include "stdafx.h"
#include "LynHideSlash1.h"


LynHideSlash1::LynHideSlash1()
{
}


LynHideSlash1::~LynHideSlash1()
{
}

void LynHideSlash1::Initialize()
{
}

void LynHideSlash1::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyn_B_Hide_SwordFlash_Exec");
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
}

void LynHideSlash1::UpdateState()
{
}

void LynHideSlash1::ExitState()
{
}
