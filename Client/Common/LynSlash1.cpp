#include "stdafx.h"
#include "LynSlash1.h"
#include "LynAttachedEffect.h"


LynSlash1::LynSlash1()
{
}


LynSlash1::~LynSlash1()
{
}

void LynSlash1::Initialize()
{
	m_slash2Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon01");
	m_slash1Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon00");

}

void LynSlash1::EnterState()
{
	ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash2Tex,L"Ç÷Ç³");
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash1");

	m_isCombo = false;


	PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_slash1_1", L"lyn_slash1_2", L"lyn_slash1_3"));

	if (m_isUpper)
	{

		// Effect
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"MeshTrail002";
		meshRenderer.mtrlName = L"Lyn_Slash1";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 0.5f;
		effectDesc.lifeTime = 0.35f;

		effectDesc.emissionBezier = Bezier({ 0.f, 0.0f }, { 0.3f, 1.0f }, { 0.7f, 1.0f }, { 1.f, 0.0f });

		effectDesc.rotateSpeed = -1000.f;
		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->SetScale(0.1f, 0.5f, 0.1f)->SetRotation(0.f, 120.f, 180.f)->SetPosition(0.f, 1.5f, 0.f);

		effect->SetParents(m_gameObject);


		// 2
		// Effect
		MeshRenderer::Desc meshRenderer2;
		meshRenderer2.meshName = L"Lyn_Attack_Vertical";
		meshRenderer2.mtrlName = L"Lyn_Slash2";
		LynAttachedEffect::Desc effectDesc2;
		effectDesc2.emissionPower = 5.f;
		effectDesc2.lifeTime = 0.35f;

		effectDesc2.emissionBezier = Bezier({ 0.f, 1.0f }, { 0.5f, 1.0f }, { 1.f, 1.0f }, { 1.f, 0.0f });

		auto effect2 = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer2)->AddComponent<LynAttachedEffect>(&effectDesc2)
			->SetScale(0.03f, 0.03f, 0.02f)->SetRotation(-90.f, 180.f, 90.f)->SetPosition(0.f, 2.5f, 1.5f);

		effect2->SetParents(m_gameObject);
	}
}

void LynSlash1::UpdateState()
{
	
	if (m_animController->IsOverTime(0.1f))
	{
		AttackInfo::Desc attack;
		attack.height = 5;
		attack.depth = 10;
		attack.width = 8;
		attack.innerPower = 1;
		CreateAttackInfo(&attack, 5.f, 1.5f, 1.f);

		//m_effect->StartWeaponTrail();
	}

	if (m_animController->IsOverTime(0.4f))
	{
		//m_effect->EndWeaponTrail();

	}

	if (BETWEEN(m_animController->GetPlayRemainTime(),0.8f,1.2f))
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
			SetState(L"slash2");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.8f)
		{
			m_animController->SetBlendOption(0.8f, 1.f, D3DXTRANSITION_FORCE_DWORD);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash1::ExitState()
{
	if (!m_isCombo)
		ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex, L"ÁúÇ³");

	//m_effect->EndWeaponTrail();
	m_info->EndSkill();
}
