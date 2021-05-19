#include "stdafx.h"
#include "LynLightningCombo.h"


LynLightningCombo::LynLightningCombo()
{
}


LynLightningCombo::~LynLightningCombo()
{
}

void LynLightningCombo::Initialize()
{

}

void LynLightningCombo::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);
	m_animController->PlayBlending("Lyn_B_Hide_LightningCombo");

	AttackInfo::Desc attack;
	attack.height = 5;
	attack.depth = 6;
	attack.width = 6;
	attack.innerPower = 1;
	attack.soundName = L"SwordMaster_Sword_Lightning_TwicePierce_ExecHit";
	CreateAttackInfo(&attack, 3.f, 1.5f, 3.5f);

	PlayOneShot(L"SwordMaster_Sword_Lightning_TwicePierce_Fire");
	VoicePlay(Nalmak_Math::Random<wstring>(L"FemaleChild01_Atk1_03", L"FemaleChild01_Atk1_04", L"FemaleChild01_Atk1_06"));

	

}

void LynLightningCombo::UpdateState()
{
	if (IsAnyMoveKeyInput())
	{
		SetState(L"idle");
		return;
	}
	

	if (m_animController->IsOverTime(0.25f))
	{
		AttackInfo::Desc attack;
		attack.height = 5;
		attack.depth = 5;
		attack.width = 8;
		attack.innerPower = 1;
		CreateAttackInfo(&attack, 3.f, 1.5f, 3.f);
	}

	if (m_animController->GetPlayRemainTime() < 1.1f)
	{
		m_info->EndSkill();

		/*if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
		{
			if (m_info->GetInnerPower() > 0)
			{
				m_info->ReduceInnerPower(1);
				SetState(L"baldo");
				return;
			}
		
		}*/
	}

	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}


}

void LynLightningCombo::ExitState()
{
	m_info->EndSkill();
}
