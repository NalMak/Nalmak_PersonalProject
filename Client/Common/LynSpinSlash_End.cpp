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
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyn_B_Std_SpinSlash_02");
	m_animController_lower->Play("Lyn_B_Std_SpinSlash_02");
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);


}

void LynSpinSlash_End::UpdateState()
{
	if (!m_animController_upper->IsPlay())
	{
		SetState(L"idle");
		return;
	}
}

void LynSpinSlash_End::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_LOWER);

	SetInteger(L"IsBlend", 1);

}
