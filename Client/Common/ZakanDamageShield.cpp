#include "stdafx.h"
#include "ZakanDamageShield.h"


ZakanDamageShield::ZakanDamageShield()
{
}


ZakanDamageShield::~ZakanDamageShield()
{
}

void ZakanDamageShield::Initialize()
{
}

void ZakanDamageShield::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_WEAK);
	m_info->LookTarget();
	m_animController->Play("Zakan_B_DamageShield_Cast");
}

void ZakanDamageShield::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_DamageShield_Cast")
	{
		if (!m_animController->IsPlay())
		{
			/*	AttackInfo::Desc info;
				info.attackType = ATTACK_TYPE_DOWN;
				info.colliderType = COLLIDER_TYPE_BOX;
				info.depth = 10.f;
				info.height = 4.f;
				info.width = 5.f;
				info.power = 3000;
				info.host = m_gameObject;
				auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);

				hitBox->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 8.f);
				hitBox->SetRotation(m_transform->GetWorldRotation());*/
			m_animController->Play("Zakan_B_DamageShield_Exec");
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.1f)
		{
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanDamageShield::ExitState()
{
}
