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
}

void LynThunderSlash::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyn_B_Hide_SwordFlash_Swing");
	m_animController_lower->Play("Lyn_B_Hide_SwordFlash_Swing");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);

	m_distanceToTarget = Nalmak_Math::Distance(m_transform->GetWorldPosition(), m_info->GetTarget()->GetTransform()->GetWorldPosition()) - 6.f;
	m_toTargetDirection = Nalmak_Math::Normalize(m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition());
	m_animPlayTime = m_animController_upper->GetAnimationClip("Lyn_B_Hide_SwordFlash_Exec")->animationSet->GetPeriod();
}

void LynThunderSlash::UpdateState()
{
	if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Swing")
	{
		m_character->SetVelocity(0, 0, 0);

		if (!m_animController_upper->IsPlay())
		{
			m_animController_upper->Play("Lyn_B_Hide_SwordFlash_Exec");
			m_animController_lower->Play("Lyn_B_Hide_SwordFlash_Exec");
		}
	}
	else if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Exec")
	{
		m_character->SetVelocity(m_toTargetDirection * m_distanceToTarget / m_animPlayTime);

		if (!m_animController_upper->IsPlay())
		{

			m_animController_upper->Play("Lyn_B_Hide_SwordFlash_End");
			m_animController_lower->Play("Lyn_B_Hide_SwordFlash_End");
		}
	}
	else if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_End")
	{
		m_character->SetVelocity(0, 0, 0);
		if (!m_animController_upper->IsPlay())
		{
			SetState(L"wait");
			return;
		}
	}
}

void LynThunderSlash::ExitState()
{
	m_character->SetVelocity(0, 0, 0);
}
