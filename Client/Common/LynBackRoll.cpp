#include "stdafx.h"
#include "LynBackRoll.h"


LynBackRoll::LynBackRoll()
{
}


LynBackRoll::~LynBackRoll()
{
}

void LynBackRoll::Initialize()
{
}

void LynBackRoll::EnterState()
{
	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_BackRoll");
	m_bnsMainCam->UnLockTarget();
}

void LynBackRoll::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}

	float ratio = m_animController->GetPlayRatio();
	if (ratio < 0.7f)
	{
		m_character->SetVelocityXZ(-m_transform->GetForward() * 25 * (0.7f - ratio));
	}
	else
		m_character->AddVelocity(0, -30 * dTime, 0);
}

void LynBackRoll::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_bnsMainCam->LockTarget();	
}
