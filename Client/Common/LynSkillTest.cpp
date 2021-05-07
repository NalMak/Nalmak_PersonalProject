#include "stdafx.h"
#include "LynSkillTest.h"


LynSkillTest::LynSkillTest()
{
}


LynSkillTest::~LynSkillTest()
{
}

void LynSkillTest::Initialize()
{
}

void LynSkillTest::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->PlayBlending("Lyn_B_defaultSlash3");
	m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,2.f,0 }, 0.4f, { 0,0 }, { 0.5f,1 }, { 1,1 }, { 1,0.f });

}

void LynSkillTest::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.1f)
	{
		m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_LINEAR);
		SetInteger(L"IsBlend", 1);
		SetState(L"idle");
		return;
	}
	
}

void LynSkillTest::ExitState()
{
	m_info->EndSkill();
}
