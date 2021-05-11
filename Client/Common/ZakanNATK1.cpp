#include "stdafx.h"
#include "ZakanNATK1.h"


ZakanNATK1::ZakanNATK1()
{
}


ZakanNATK1::~ZakanNATK1()
{
}

void ZakanNATK1::Initialize()
{
}

void ZakanNATK1::EnterState()
{
	m_animController->Play("Zakan_B_Std_NATK1_Cast");
}

void ZakanNATK1::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_NATK1_Cast")
	{
		if (!m_animController->IsPlay())
		{
			CreateAttackArea();
			m_animController->Play("Zakan_B_Std_NATK1_Exec");
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.1f)
		{
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"peace_idle");
			return;
		}
	}

		
		
}

void ZakanNATK1::ExitState()
{
}

void ZakanNATK1::CreateAttackArea()
{
	AttackInfo::Desc info;
	info.attackType = ATTACK_TYPE_DOWN;
	info.colliderType = COLLIDER_TYPE_BOX;
	info.depth = 5.f;
	info.height = 4.f;
	info.width = 5.f;
	info.power = 100;
	auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO,OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);

	hitBox->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 3.f);
}
