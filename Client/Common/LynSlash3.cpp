#include "stdafx.h"
#include "LynSlash3.h"
#include "LynAttachedEffect.h"


LynSlash3::LynSlash3()
{
}

LynSlash3::~LynSlash3()
{
}

void LynSlash3::Initialize()
{
	m_slash1Tex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon00");
}

void LynSlash3::EnterState()
{
	ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex,L"ÁúÇ³");
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.5f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash3");

	m_isCombo = false;


	PlayOneShot(Nalmak_Math::Random<wstring>(L"lyn_slash3_1", L"lyn_slash3_2", L"lyn_slash3_3"));
	
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
		Quaternion rot;
		Matrix mat;
		D3DXQuaternionRotationYawPitchRoll(&rot,0.f, 0.f, -90.f* Deg2Rad);
		D3DXMatrixRotationQuaternion(&mat, &rot);
		Vector3 yAxis;
		memcpy(&yAxis, &mat._21, sizeof(Vector3));
		effectDesc.rotateAxis = yAxis;
		effectDesc.rotateSpeed = 650.f;
		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->SetScale(0.25f, 0.8f, 0.25f)->SetRotation(-120.f, 0.f, -90.f)->SetPosition(-0.5f, 2.3f, 0.5f);

		effect->SetParents(m_gameObject);
	}
}

void LynSlash3::UpdateState()
{

	if (m_animController->IsOverTime(0.1f))
	{
		AttackInfo::Desc attack;
		attack.height = 5;
		attack.depth = 10;
		attack.width = 8;
		attack.innerPower = 2;
		CreateAttackInfo(&attack, 5.f, 1.5f, 1.3f);

		m_effect->StartWeaponTrail();
	}


	if (m_animController->GetPlayRemainTime() < 0.6f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.4)
		{
			m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash1");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.4)
		{
			m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}

	
}

void LynSlash3::ExitState()
{
	if (!m_isCombo)
		ChangeSkillSlotTexture(BNS_SKILL_SLOT_LB, m_slash1Tex,L"ÁúÇ³");

	m_effect->EndWeaponTrail();

	m_info->EndSkill();
}
