#include "stdafx.h"
#include "BnS_AttackArea.h"
#include "ZakanNATK2.h"


ZakanNATK2::ZakanNATK2()
{
}


ZakanNATK2::~ZakanNATK2()
{
}

void ZakanNATK2::Initialize()
{
}

void ZakanNATK2::EnterState()
{
	m_effect->StartSwordTrail();

	m_info->SetBattleState(BATTLE_STATE_WEAK);
	m_info->LookTarget();
	m_animController->Play("Zakan_B_Std_NATK2_Cast");

	m_transform->UpdateMatrix();

	BnS_AttackArea::Desc areaDesc;
	areaDesc.timer = 0.65f;
	areaDesc.mtrlName = L"zakan_attackAreaRect";
	auto area = INSTANTIATE()->AddComponent<BnS_AttackArea>(&areaDesc);
	area->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 9.f + Vector3(0, 0.01f, 0))->SetScale(10.f, 1.5f, 18.f);
	area->SetRotation(m_transform->GetWorldRotation());
}

void ZakanNATK2::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_NATK2_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_effect->PlayDust();
			m_effect->PlayNATK();

			AttackInfo::Desc info;
			info.attackType = ATTACK_TYPE_DOWN;
			info.colliderType = COLLIDER_TYPE_BOX;
			info.depth = 18.f;
			info.height = 6.f;
			info.width = 10.f;
			info.power = 3000;
			info.host = m_gameObject;
			auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);

			hitBox->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 9.f);
			hitBox->SetRotation(m_transform->GetWorldRotation());
			m_animController->Play("Zakan_B_Std_NATK2_Exec");

			m_audio->PlayOneShot(L"zakan_NATK");
		}
	}
	else
	{
		if (m_animController->IsOverTime(0.4f))
		{
			m_effect->EndSwordTrail();
		}

		if (m_animController->GetPlayRemainTime() < 0.1f)
		{
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanNATK2::ExitState()
{
	m_effect->EndSwordTrail();

}
