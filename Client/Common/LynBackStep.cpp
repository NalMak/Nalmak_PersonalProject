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
	m_effect->StartBodyTrail();
	m_info->SetResistance(true);
	AddInnerPower(2);

	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 2.f;
		buff.key = L"SS";
		buff.skill = m_skillController->GetSkill(L"backStep");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);


	}
	PlayOneShot(L"Fencer_BackStep_Shot");


	m_info->StartSkill();

	if (m_info->GetState() == LYN_STATE_BATTLE_HIDEBLADE)
	{
		m_animController->PlayBlending("Lyn_B_Hide_BackStep");
	}
	else
	{
		m_info->SetState(LYN_STATE_BATTLE_STANDARD);
		m_animController->PlayBlending("Lyn_B_Std_BackStep");
	}

	//m_animController->SetRootMotion(true);


}

void LynBackStep::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.1f)
	{
		m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	float ratio = m_animController->GetPlayRatio();
	if (ratio < 0.7f)
	{
		m_character->SetVelocityXZ(-m_transform->GetForward() * 155 * (0.7f - ratio));
		//m_character->SetVelcityXZ(Vector3(1, 1, 1));
	}
	else
		m_character->AddVelocity(0, -30 * dTime, 0);

}

void LynBackStep::ExitState()
{
	//m_animController->SetRootMotion(false);
	m_info->SetResistanceTimer(1.f);
	m_info->SetResistance(false);
	m_character->AddVelocity(0, -30 * dTime, 0);
	m_info->EndSkill();
	m_effect->EndBodyTrail();

}
