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
	attack.depth = 10;
	attack.width = 6;
	attack.innerPower = 1;
	attack.soundName = L"SwordMaster_Sword_Lightning_TwicePierce_ExecHit";
	auto effect = CreateAttackInfo(&attack, 3.f, 1.5f, 3.f);

	if (effect)
	{
		PointLight::Desc point;
		point.color = Vector3(0.85f, 0.9f, 1.f);
		point.radius = 10.f;
		point.diffuseIntensity = 3.5f;
		effect->AddComponent<PointLight>(&point);
	}



	PlayOneShot(L"SwordMaster_Sword_Lightning_TwicePierce_Fire");
	VoicePlay(Nalmak_Math::Random<wstring>(L"FemaleChild01_Atk1_03", L"FemaleChild01_Atk1_04", L"FemaleChild01_Atk1_06"));

	m_effect->StartWeaponTrail();
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
		auto effect =  CreateAttackInfo(&attack, 5.f, 1.5f, 3.5f, [=]()
		{
			m_effect->PlayLightningComboEffect();
		});

		if (effect)
		{
			PointLight::Desc point;
			point.color = Vector3(0.85f, 0.9f, 1.f);
			point.radius = 10.f;
			point.diffuseIntensity = 3.5f;
			effect->AddComponent<PointLight>(&point);
		}
	}

	if (m_animController->GetPlayRemainTime() < 1.f)
	{
		m_info->EndSkill();
	}

	if (m_animController->IsOverTime(0.6f))
	{
		m_effect->EndWeaponTrail();
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
	m_effect->EndWeaponTrail();

	m_info->EndSkill();
}
