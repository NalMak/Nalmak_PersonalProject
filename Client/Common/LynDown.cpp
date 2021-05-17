#include "stdafx.h"
#include "LynDown.h"


LynDown::LynDown()
{
}


LynDown::~LynDown()
{
}

void LynDown::Initialize()
{
}

void LynDown::EnterState()
{
	m_info->SetSpeed(0);
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->PlayBlending("Lyn_B_Down_B");
	m_bnsMainCam->UnLockTarget();
	m_info->SetBattleState(BATTLE_STATE_DOWN);
	m_info->ChangeSkillByState(LYN_SKILL_STATE_CC);

	if (m_isUpper)
	{
		m_character->AddVelocity(Vector3(0, 15, 0));
	}
}


void LynDown::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Down_B")
	{
		m_character->SetVelocityXZ(-m_transform->GetForward() * 3.5f);
		if (!m_animController->IsPlay())
		{
			m_animController->SetBlendOption(0.25f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"layDown");
			return;
		}
	}
}

void LynDown::ExitState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_bnsMainCam->LockTarget();
}
