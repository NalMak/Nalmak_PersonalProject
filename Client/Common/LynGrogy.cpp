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
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->PlayBlending("Lyn_B_Stun_Start");
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

	if (!m_animController->IsPlay("Lyn_B_Stun_Start"))
	{
		m_animController->Play("Lyn_B_Stun_Looping");
	}
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Stun_Looping")
	{
		if (m_ccTime > 0)
		{
			m_ccTime -= dTime;
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}

}

void LynGrogy::ExitState()
{
	m_bnsMainCam->LockTarget();
}
