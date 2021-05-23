#include "stdafx.h"
#include "LynSlash2.h"
#include "LynAttachedEffect.h"


LynSlash2::LynSlash2()
{
}

LynSlash2::~LynSlash2()
{
}

void LynSlash2::Initialize()
{
	m_slash3Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon02");
	m_slash1Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon00");

}

void LynSlash2::EnterState()
{
	ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash3Tex, L"ÆøÇ³");

	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash2");



	m_isCombo = false;


	PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_slash2_2", L"lyn_slash2_3"));

	if (m_isUpper)
	{
		// Effect
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"MeshTrail002";
		meshRenderer.mtrlName = L"Lyn_Slash1";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 0.3f;
		effectDesc.lifeTime = 0.32f;
		
		effectDesc.emissionBezier = Bezier({ 0.f, 0.0f }, { 0.3f, 1.0f }, { 0.7f, 1.0f }, { 1.f, 0.0f });

		effectDesc.rotateSpeed = 650.f;
		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->SetScale(0.25f, 0.8f, 0.25f)->SetRotation(0.f, -120.f, 0.f)->SetPosition(0.f, 2.5f, 0.f);

		effect->SetParents(m_gameObject);
	}

}

void LynSlash2::UpdateState()
{
	if (m_animController->IsOverTime(0.15f))
	{
		AttackInfo::Desc attack;
		attack.height = 5;
		attack.depth = 10;
		attack.width = 8;
		attack.innerPower = 1;
		CreateAttackInfo(&attack, 5.f, 1.5f, 1.f);

		m_effect->StartWeaponTrail();
	}

	if (BETWEEN(m_animController->GetPlayRemainTime(), 0.8f, 1.2f))
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	

	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.8f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash3");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.6f)
		{
			m_animController->SetBlendOption(0.6f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash2::ExitState()
{
	if(!m_isCombo)
		ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex, L"ÁúÇ³");

	m_effect->EndWeaponTrail();

	m_info->EndSkill();
}
