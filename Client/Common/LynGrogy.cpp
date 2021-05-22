#include "stdafx.h"
#include "LynGrogy.h"


LynGrogy::LynGrogy()
{
}


LynGrogy::~LynGrogy()
{
}

void LynGrogy::Initialize()
{
}

void LynGrogy::EnterState()
{
	m_info->SetSpeed(0);
	m_info->SetBattleState(BATTLE_STATE_GROGY);
	m_info->ChangeSkillByState(LYN_SKILL_STATE_GROGY);


	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->PlayBlending("Lyn_B_Grogy_Start");
	m_bnsMainCam->UnLockTarget();
	m_backRollTimer = 1.f;

	m_ccTime = GetFloat(L"grogyTime");
}

void LynGrogy::UpdateState()
{
	if (m_backRollTimer > 0)
	{
		m_backRollTimer -= dTime;
	}
	else
	{
		m_skillController->ReleaseSkill(BNS_SKILL_SLOT_F);
	}
	
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Grogy_End")
	{
		if (m_animController->GetPlayRemainTime() < 0.2f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
	else
	{
		if (m_ccTime > 0)
		{
			m_ccTime -= dTime;
		}
		else
		{
			m_animController->PlayBlending("Lyn_B_Grogy_End");
		}
	}
}

void LynGrogy::ExitState()
{
	if (m_isUpper)
	{
		m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
		m_info->SetBattleState(BATTLE_STATE_WEAK);

		m_bnsMainCam->LockTarget();
	}

}
