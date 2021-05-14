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
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Down_B");
	m_bnsMainCam->UnLockTarget();

	m_skillController->ChangeSkillSlotByAnimation(L"backRoll");
}

void LynDown::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F))
	{
		if (BETWEEN(m_animController->GetPlayRatio(), 0.4f, 1.f))
		{
			SetState(L"backRoll");
			return;
		}
	}

	

	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Down_B")
	{
		m_character->SetVelocityXZ(-m_transform->GetForward() * 3.5f);
		if (m_animController->GetPlayRemainTime() < 0.25f)
		{
			m_animController->SetBlendOption(0.25f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"layDown");
			return;
		}
	}
}

void LynDown::ExitState()
{
	m_skillController->ReleaseSkill(BNS_SKILL_SLOT_F);

	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_bnsMainCam->LockTarget();
}
