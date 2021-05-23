#include "stdafx.h"
#include "LynCrash.h"


LynCrash::LynCrash()
{
}


LynCrash::~LynCrash()
{
}

void LynCrash::Initialize()
{
}

void LynCrash::EnterState()
{
	m_info->StartSkill();

	m_animController->Play("Lyn_B_Crash");
}

void LynCrash::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynCrash::ExitState()
{
	m_info->EndSkill();
	m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
}
