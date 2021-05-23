#include "stdafx.h"
#include "ZakanSplitBlood.h"
#include "BnS_AttackArea.h"



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
	m_effect->StartSwordTrail();

	m_animController->Play("Zakan_SplitBlood_Cast");
	m_audio->PlayOneShot(L"zakan_splitBlood");


	m_info->LookTarget();

	m_transform->UpdateMatrix();
	BnS_AttackArea::Desc areaDesc;
	areaDesc.timer = 1.2f;
	areaDesc.mtrlName = L"zakan_attackAreaRect2";
	auto area = INSTANTIATE()->AddComponent<BnS_AttackArea>(&areaDesc);
	area->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 100.f + Vector3(0, 0.01f, 0) - m_transform->GetRight() * 2)->SetScale(10.f, 1.5f, 200.f);
	area->SetRotation(m_transform->GetWorldRotation());
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
			info.width = 10.f;
			info.power = 4500;
			info.host = m_gameObject;
		
			auto attack = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);
			attack->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 50.f );
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
	m_effect->EndSwordTrail();

}
