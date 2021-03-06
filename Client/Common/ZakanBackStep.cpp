#include "stdafx.h"
#include "ZakanBackStep.h"


ZakanBackStep::ZakanBackStep()
{
}


ZakanBackStep::~ZakanBackStep()
{
}

void ZakanBackStep::Initialize()
{
	auto animClip = m_animController->GetAnimationClip("Zakan_B_Spell_Skl_Teleport_Fire");
	m_flyTime = (float)animClip->animationSet->GetPeriod() / animClip->speed;
}

void ZakanBackStep::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_animController->Play("Zakan_B_Spell_Skl_Teleport_Cast");
	m_audio->PlayOneShot(L"zakan_teleport");

}

void ZakanBackStep::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Teleport_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Skl_Teleport_Fire");

			Vector3 dir = Nalmak_Math::Normalize(m_info->GetSpawnPos() - m_transform->GetWorldPosition());
			m_landingTarget =  m_transform->GetWorldPosition() + dir * 17 / BNS_DISTANCE_RATIO;
			m_jumpPos = m_transform->GetWorldPosition();
			m_flyVelocity = (m_landingTarget - m_jumpPos) / m_flyTime;
			m_flyLength = Nalmak_Math::Distance(Vector3(m_jumpPos.x, m_landingTarget.y, m_jumpPos.z), m_landingTarget);
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Teleport_Fire")
	{
		m_character->SetVelocityXZ(m_flyVelocity * Nalmak_Math::Clamp(2.f - m_animController->GetPlayRatio(), 0.5f, 0.9f));
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
			if (GetInteger(L"IsPattern") == 1)
				SetState(L"pattern");
			else
				SetState(L"area360");
			return;
		}
	}
}

void ZakanBackStep::ExitState()
{
}
