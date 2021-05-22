#include "stdafx.h"
#include "ZakanDown.h"



ZakanDown::ZakanDown()
{
}


ZakanDown::~ZakanDown()
{
}

void ZakanDown::Initialize()
{
	m_stateControl->SetInteger(L"downExtension", 0);
}

void ZakanDown::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_DOWN);

	m_downTimer = GetFloat(L"down");


	if (GetInteger(L"downExtension") == 0)
	{
		m_animController->Play("Zakan_B_Std_Down_Front_Start");
	}
}

void ZakanDown::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_Down_Front_Start")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Std_Down_Front_Looping");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_Down_Front_Looping")
	{
		if (m_downTimer > 0)
		{
			m_downTimer -= dTime;
		}
		else
		{
			SetState(L"rise");
		}
	}
	
}

void ZakanDown::ExitState()
{
}
