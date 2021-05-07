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
	m_info->SetState(LYN_STATE_BATTLE_HIDEBLADE);
	m_animController->Play("Lyn_B_Hide_SwordFlash_Swing");

	m_distanceToTarget = Nalmak_Math::Distance(m_transform->GetWorldPosition(), m_info->GetTarget()->GetTransform()->GetWorldPosition()) - 6.f;
	m_toTargetDirection = Nalmak_Math::Normalize(m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition());
	m_animPlayTime = m_animController->GetAnimationClip("Lyn_B_Hide_SwordFlash_Exec")->animationSet->GetPeriod();
	m_info->StartSkill();
}

void LynThunderSlash::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Swing")
	{
		m_character->SetVelocity(0, 0, 0);

		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Hide_SwordFlash_Exec");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Exec")
	{
		m_character->SetVelocity(m_toTargetDirection * m_distanceToTarget / (float)m_animPlayTime);

		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Hide_SwordFlash_End");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_End")
	{
		m_character->SetVelocity(0, 0, 0);
		if (m_animController->GetPlayRemainTime() < 0.2)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_LINEAR);
			SetInteger(L"IsBlend", 1);
			SetState(L"idle");
			return;
		}
	}
}

void LynThunderSlash::ExitState()
{
	m_character->SetVelocity(0, 0, 0);
	m_info->EndSkill();

}
