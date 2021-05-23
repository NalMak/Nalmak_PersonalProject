#include "stdafx.h"
#include "LynSpinSlash_Start.h"
#include "TestEffectMesh.h"
#include "MeshEffect_Slash.h"
#include "LynAttachedEffect.h"
#include "LynSpinSlashEffect.h"


LynSpinSlash_Start::LynSpinSlash_Start()
{
}


LynSpinSlash_Start::~LynSpinSlash_Start()
{
}

void LynSpinSlash_Start::Initialize()
{
	m_attack.soundName = L"SwordMaster_SpinSlash_Shot";
	m_attack.colliderType = COLLIDER_TYPE_SPHERE;
	m_attack.radius = 7.f;
	m_attack.isCritical = false;
}

void LynSpinSlash_Start::EnterState()
{
	m_effect = nullptr;

	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_SpinSlash_01");
	m_info->StartSkill();
	PlayOneShot(L"lyn_spinSlash");


	if (m_isUpper)
	{
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"FlatCircle";
		meshRenderer.mtrlName = L"Lyn_SpinSlash";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 1.2f;
		effectDesc.lifeTime = 1.4f;
		effectDesc.rotateSpeed = 0.f;
		effectDesc.emissionBezier = Bezier({ 0,0 }, { 0,0.532594f }, { 0.347059f,0.336765f }, { 1,0 });
		LynSpinSlashEffect::Desc spin;
		spin.boneName = "WeaponR";
		spin.host = m_gameObject;
		m_effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->AddComponent<LynSpinSlashEffect>(&spin);

		m_effect->GetTransform()->SetScale(0.12f, 0.12f, 0.12f);
	}
	//m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,-0.5f,0 }, 0.75f, { 0,0 }, { 0.179f,0.01f }, { 0.82f,0.75f }, { 1,0 });
}

void LynSpinSlash_Start::UpdateState()
{
	if (m_animController->IsOverTime(0.32f))
	{
		m_attack.isCritical = false;
		CreateAttackInfo(&m_attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(0.45f))
	{
		m_attack.isCritical = false;
		CreateAttackInfo(&m_attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(0.7f))
	{
		m_attack.isCritical = false;
		CreateAttackInfo(&m_attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(0.88f))
	{
		m_attack.isCritical = false;
		CreateAttackInfo(&m_attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(1.06f))
	{
		m_attack.isCritical = false;
		CreateAttackInfo(&m_attack, 0.f, 1.f, 0.3f);
	}
	if (!m_animController->IsPlay())
	{
		SetState(L"spinSlash_end");
	}
}

void LynSpinSlash_Start::ExitState()
{
	m_info->EndSkill();
	m_info->SetBattleState(BATTLE_STATE_WEAK);

	DESTROY(m_effect);
}
