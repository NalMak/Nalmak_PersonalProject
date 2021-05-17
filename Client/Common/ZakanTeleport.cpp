#include "stdafx.h"
#include "ZakanTeleport.h"



ZakanTeleport::ZakanTeleport()
{
}


ZakanTeleport::~ZakanTeleport()
{
}

void ZakanTeleport::Initialize()
{
	auto animClip = m_animController->GetAnimationClip("Zakan_B_Spell_Skl_Teleport_Fire");
	m_flyTime = (float)animClip->animationSet->GetPeriod() / animClip->speed;

}

void ZakanTeleport::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_animController->Play("Zakan_B_Spell_Skl_Teleport_Cast");

}

void ZakanTeleport::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Teleport_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Skl_Teleport_Fire");

			m_landingTarget = m_info->GetTarget()->GetTransform()->GetWorldPosition();
			m_jumpPos = m_transform->GetWorldPosition();
			m_flyVelocity = (m_landingTarget - m_jumpPos) / m_flyTime;
			m_flyLength = Nalmak_Math::Distance(Vector3(m_jumpPos.x, m_landingTarget.y, m_jumpPos.z), m_landingTarget);
			m_character->SetVelocityY(160);
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Teleport_Fire")
	{
		m_character->AddVelocity(Vector3(0,-700 * dTime,0));

		m_character->SetVelocityXZ(m_flyVelocity * Nalmak_Math::Clamp(0.9f - m_animController->GetPlayRatio(), 0.5f, 0.9f));
		Vector3 worldPos = m_transform->GetWorldPosition();
		if (Nalmak_Math::Distance(Vector3(worldPos.x, m_landingTarget.y, worldPos.z), m_jumpPos) > m_flyLength)
		{
			m_animController->Play("Zakan_B_Spell_Skl_Teleport_End");
			m_character->SetVelocity(Vector3(0, 0, 0));

		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Teleport_End")
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}

}

void ZakanTeleport::ExitState()
{
}
