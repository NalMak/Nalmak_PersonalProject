#include "stdafx.h"
#include "ZakanSplitBlood.h"



ZakanSplitBlood::ZakanSplitBlood()
{
}


ZakanSplitBlood::~ZakanSplitBlood()
{
}

void ZakanSplitBlood::Initialize()
{
}

void ZakanSplitBlood::EnterState()
{
	m_animController->Play("Zakan_SplitBlood_Cast");
	m_audio->PlayOneShot(L"zakan_splitBlood");

	m_info->LookTarget();
}

void ZakanSplitBlood::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_SplitBlood_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_SplitBlood_Exec");

			AttackInfo::Desc info;
			info.attackType = ATTACK_TYPE_KNOCKBACK_LONG;
			info.colliderType = COLLIDER_TYPE_BOX;
			info.depth = 100.f;
			info.height = 10.f;
			info.width = 15.f;
			info.power = 4500;
			info.host = m_gameObject;
		
			auto attack = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);
			attack->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 50.f);
			attack->GetTransform()->rotation = m_transform->GetWorldRotation();
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_SplitBlood_Exec")
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanSplitBlood::ExitState()
{
}
