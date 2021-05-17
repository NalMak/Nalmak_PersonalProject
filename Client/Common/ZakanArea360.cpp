#include "stdafx.h"
#include "ZakanArea360.h"



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
			info.depth = 8.f;
			info.height = 6.f;
			info.width = 25.f;
			info.power = 3000;
			info.lifeTime = 2.f;
			info.host = m_gameObject;
			RigidBody::Desc rigid;
			rigid.isGravity = false;
			rigid.velocity = m_transform->GetForward() * 300;
			auto attack = INSTANTIATE(OBJECT_TAG_ATTACKINFO,OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info)->AddComponent<RigidBody>(&rigid);
			attack->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 4);
			attack->GetTransform()->rotation = m_transform->GetWorldRotation();
		}
	}
	else
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanArea360::ExitState()
{
}
