#include "stdafx.h"
#include "LynThunderSlash.h"


LynThunderSlash::LynThunderSlash()
{
}


LynThunderSlash::~LynThunderSlash()
{
}

void LynThunderSlash::Initialize()
{
	m_speed = 180;
}

void LynThunderSlash::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_HIDEBLADE);
	m_animController->Play("Lyn_B_Hide_SwordFlash_Swing");

	Vector3 dir = m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition();
	dir.y = 0;
	m_direction = Nalmak_Math::Normalize(dir);

	m_targetPosition = m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_direction * 3.5f / BNS_DISTANCE_RATIO;
	m_targetPosition.y = 0;

	m_targetDistance = Nalmak_Math::Distance(m_transform->GetWorldPosition(), m_targetPosition);

	m_character->SetVelocity(m_direction * m_speed);

	m_startPosition = m_transform->GetWorldPosition();

	m_info->StartSkill();
	
	m_transform->LookAt_RotYAxis(m_direction);

	m_bnsMainCam->UnLockTarget();

	PlayOneShot(L"SwordMaster_Sword_Wind_GodSlash_Fire1-1");

}

void LynThunderSlash::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Swing")
	{
		m_character->SetVelocityXZ(m_direction * m_speed);

		if (Nalmak_Math::Distance(m_startPosition, m_transform->GetWorldPosition()) > m_targetDistance)
		{
			AttackInfo::Desc attack;
			attack.depth = 8.f;
			attack.width = 6.f;
			attack.height = 4.f;
			CreateAttackInfo(&attack,5.f,2.f,2.f);

			m_character->SetVelocity(0, 0, 0);
			m_animController->Play("Lyn_B_Hide_SwordFlash_Exec");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Exec")
	{
		if (m_animController->GetPlayRemainTime() < 0.1f)
		{
			m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}

}

void LynThunderSlash::ExitState()
{
	m_bnsMainCam->LockTarget();

	m_character->SetVelocity(0, 0, 0);
	m_info->EndSkill();

}
