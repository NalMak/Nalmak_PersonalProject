#include "stdafx.h"
#include "LynBaldo.h"
#include "LynAttachedEffect.h"


LynBaldo::LynBaldo()
{
}


LynBaldo::~LynBaldo()
{
}

void LynBaldo::Initialize()
{
}

void LynBaldo::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->PlayBlending("Lyn_B_Hide_Baldo0");
	PlayOneShot(L"SwordMaster_G3_Hit_Small");
	VoicePlay(L"FemaleChild01_sk_B_ShortShot03");

	
	if (m_isUpper)
	{
		AttackInfo::Desc attack;
		attack.attackType = ATTACK_TYPE_DEFAULT;
		attack.colliderType = COLLIDER_TYPE_BOX;
		attack.depth = 10.f;
		attack.height = 3.f;
		attack.width = 4.f;
		attack.soundName = L"Fencer_Batto_Fire_Hit";
		attack.host = m_gameObject;
		attack.power = (UINT)(m_info->m_power * 3 * Nalmak_Math::Rand(0.8f, 1.2f));
		float critical = Nalmak_Math::Rand(0.f, 1.f);
		attack.isCritical = m_info->m_criticalRatio > critical;
		
		auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
			->AddComponent<AttackInfo>(&attack)
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 5 + Vector3(0, 2, 0))
			->SetRotation(m_transform->GetWorldRotation());

	

		if (attack.isCritical)
		{
			hitBox->GetComponent<AttackInfo>()->AddHitEvent([=]()
			{
				m_info->AddLightningSpirit();
				m_effect->PlayBaldoEffect();
			});
		}
		else
		{
			hitBox->GetComponent<AttackInfo>()->AddHitEvent([=]()
			{
				m_effect->PlayBaldoEffect();
			});
		}

		

		// Effect
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"Tornado02";
		meshRenderer.mtrlName = L"Lyn_Baldo";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 13.5f;
		effectDesc.lifeTime = 0.15f;
		effectDesc.yAxisAngle = 90;
		effectDesc.emissionBezier = Bezier({0.f, 0.0f}, {0.5f, 0.0588235f }, {1.f, 1.f}, {1.f, 0.f});

		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->SetScale(0.065f, 0.065f, 0.07f)->SetRotation(0.f, 150.f, 0.f)->SetPosition(0.f, 1.4f, 0.8f);
	
		Quaternion rot;
		Vector3 axis = { 0,0,1 };
		axis = Nalmak_Math::Normalize(axis);
		D3DXQuaternionRotationAxis(&rot, &axis, 30 * Deg2Rad);
		effect->GetTransform()->rotation *= rot;

		effect->SetParents(m_gameObject);
		
	}
}

void LynBaldo::UpdateState()
{
	if (IsAnyMoveKeyInput())
	{
		SetState(L"idle");
		return;
	}

	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);

		
	}

	if (m_animController->GetPlayRemainTime() < 0.4f)
	{
		m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	
}

void LynBaldo::ExitState()
{
	m_info->EndSkill();
}
