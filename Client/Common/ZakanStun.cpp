#include "stdafx.h"
#include "ZakanStun.h"



ZakanStun::ZakanStun()
{
}


ZakanStun::~ZakanStun()
{
}

void ZakanStun::Initialize()
{
}

void ZakanStun::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_STUN);

	m_stunTimer = GetFloat(L"ccTime");
	m_animController->Play("Zakan_B_Std_Stun_Start");
}

void ZakanStun::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_Stun_Start")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Std_Stun_Looping");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_Stun_Looping")
	{
		if (m_stunTimer > 0)
		{
			m_stunTimer -= dTime;
		}
		else
		{
			SetState(L"battle_idle");
		}
	}
	else
	{
		SetState(L"battle_idle");
		return;
	}
}

void ZakanStun::ExitState()
{
}
