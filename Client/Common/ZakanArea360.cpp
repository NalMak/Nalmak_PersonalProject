#include "stdafx.h"
#include "ZakanArea360.h"
#include "MeshEffect_Slash.h"
#include "BnS_AttackArea.h"
#include "BnS_AttackArea_ScaleAnim.h"



ZakanArea360::ZakanArea360()
{
}


ZakanArea360::~ZakanArea360()
{
}

void ZakanArea360::Initialize()
{
}

void ZakanArea360::EnterState()
{
	m_info->LookTarget();
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_animController->Play("Zakan_B_Spell_Skl_Area360_Cast");
	m_effect->StartSwordTrail();

	m_transform->UpdateMatrix();
	BnS_AttackArea_ScaleAnim::Desc areaDesc;
	areaDesc.startScale = Vector3(0.f, 1.5f, 200.f);
	areaDesc.targetScale = Vector3(26.f, 1.5f, 200.f);
	areaDesc.lifeTime = 1.2f;
	auto area = INSTANTIATE()->AddComponent<BnS_AttackArea_ScaleAnim>(&areaDesc);
	area->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 100.f + Vector3(0, 0.01f, 0) - m_transform->GetRight() * 2);
	area->SetRotation(m_transform->GetWorldRotation());

}

void ZakanArea360::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Area360_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Skl_Area360_Exec");
			AttackInfo::Desc info;
			info.attackType = ATTACK_TYPE_KNOCKBACK_MIDDLE;
			info.colliderType = COLLIDER_TYPE_BOX;
			info.depth = 26.f;
			info.height = 6.f;
			info.width = 10.f;
			info.power = 4000;
			info.lifeTime = 2.f;
			info.host = m_gameObject;
			RigidBody::Desc rigid;
			rigid.isGravity = false;
			rigid.velocity = m_transform->GetForward() * 300;
			MeshRenderer::Desc mesh;
			mesh.mtrlName = L"zakan_360area";
			mesh.meshName = L"zakan_em_projectile";
			MeshEffect_Slash::Desc effect;
			effect.emissionChange = -0.5f;
			effect.scaleChange = { 0,1.f,0.f };
			auto attack = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<MeshEffect_Slash>(&effect)
				->AddComponent<AttackInfo>(&info)->AddComponent<RigidBody>(&rigid)->AddComponent<MeshRenderer>(&mesh)->SetScale(0.05f, 0.2f, 0.05f);
			attack->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 3.f + Vector3(0, 1.f, 0));
			attack->GetTransform()->rotation = m_transform->GetWorldRotation() * BNS_ROT_YAXIS_90;

		}
	}
	else
	{
		if (m_animController->IsOverTime(0.3f))
		{
			m_effect->EndSwordTrail();
		}
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanArea360::ExitState()
{
	m_effect->EndSwordTrail();
}
