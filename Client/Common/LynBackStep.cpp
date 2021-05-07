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
	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_BackStep");


	m_animController->SetRootMotion(true);


}

void LynBackStep::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.1f)
	{
		SetState(L"idle");
		return;
	}
	float ratio = m_animController->GetPlayRatio();
	if(ratio < 0.7f)
		m_character->SetVelocity(-m_transform->GetForward() * 140 * (0.7f - ratio));
	else
		m_character->AddVelocity(0, -30 * dTime, 0);

}

void LynBackStep::ExitState()
{
	m_animController->SetRootMotion(false);

	m_character->AddVelocity(0, -30 * dTime, 0);
	m_info->EndSkill();

	SetInteger(L"IsBlend", 0);
}
