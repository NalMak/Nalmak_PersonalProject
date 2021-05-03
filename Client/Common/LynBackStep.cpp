#include "stdafx.h"
#include "LynBackStep.h"


LynBackStep::LynBackStep()
{
}


LynBackStep::~LynBackStep()
{
}

void LynBackStep::Initialize()
{
}

void LynBackStep::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);

	m_animController_upper->Play("Lyn_B_Std_BackStep");
	m_animController_lower->Play("Lyn_B_Std_BackStep");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);


	m_animController_upper->SetRootMotion(true);
	m_animController_lower->SetRootMotion(true);

}

void LynBackStep::UpdateState()
{
	if (!m_animController_lower->IsPlay())
	{
		SetState(L"wait");
		return;
	}
	float ratio = m_animController_lower->GetPlayRatio();
	if(ratio < 0.7f)
		m_character->SetVelocity(-m_transform->GetForward() * 140 * (0.7 - ratio));
	else
		m_character->AddVelocity(0, -30 * dTime, 0);

}

void LynBackStep::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_LOWER);

	m_animController_upper->SetRootMotion(false);
	m_animController_lower->SetRootMotion(false);
	m_character->AddVelocity(0, -30 * dTime, 0);

	SetInteger(L"IsBlend", 0);
}
