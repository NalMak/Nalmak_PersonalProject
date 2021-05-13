#include "stdafx.h"
#include "ZakanMove.h"

ZakanMove::ZakanMove()
{
}

ZakanMove::~ZakanMove()
{
}

void ZakanMove::Initialize()
{
}

void ZakanMove::EnterState()
{
	m_animController->Play("Zakan_B_Std_RunFront");
}

void ZakanMove::UpdateState()
{
	if (m_info->GetTarget())
	{
		if (m_info->GetDistanceToTarget() > 5)
		{
			m_info->LookTarget();
			Vector3 velocity = m_transform->GetForward() * 10;
			m_character->SetVelocityX(velocity.x);
			m_character->SetVelocityZ(velocity.z);
		}
		else
		{
			SetState(L"battle_idle");
			return;
		}
	}
	else
	{
		m_info->LookTarget();
		Vector3 velocity = m_transform->GetForward() * 10;
		m_character->SetVelocityX(velocity.x);
		m_character->SetVelocityZ(velocity.z);

		if (Nalmak_Math::DistanceSq(m_transform->GetWorldPosition(), m_info->GetSpawnPos()) < 15.f)
		{
			SetState(L"peace_idle");
			return;
		}
	}
	
}

void ZakanMove::ExitState()
{
}
