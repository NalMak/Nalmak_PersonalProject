#include "stdafx.h"
#include "LynIlSum.h"


LynIlSum::LynIlSum()
{
}


LynIlSum::~LynIlSum()
{
}

void LynIlSum::Initialize()
{
}

void LynIlSum::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);
	m_animController->PlayBlending("Lyn_B_Hide_Ilsum");
	PlayOneShot(L"Fencer_Stab_Hit");

	AttackInfo::Desc attack;
	attack.depth = 16.f;
	attack.height = 5.f;
	attack.width = 9.f;
	attack.innerPower = 1;
	CreateAttackInfo(&attack, 8.f, 2.f, 5.f);

}

void LynIlSum::UpdateState()
{
	float ratio = m_animController->GetPlayRatio();
	if (ratio < 0.4f)
	{
		m_character->SetVelocityXZ(m_transform->GetForward() * 100 * pow((0.4f - ratio )/ 0.4f,2));
	}
	else
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			SetState(L"ilsum");
			return;
		}

		m_character->SetVelocityXZ({ 0,0,0 });
	}

	if (m_animController->GetPlayRemainTime() < 2.f)
	{
		m_info->EndSkill();
	}

	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynIlSum::ExitState()
{
	m_info->EndSkill();

}
