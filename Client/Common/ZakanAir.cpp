#include "stdafx.h"
#include "ZakanAir.h"



ZakanAir::ZakanAir()
{
}


ZakanAir::~ZakanAir()
{
}

void ZakanAir::Initialize()
{
}

void ZakanAir::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_AIR);
	m_animController->Play("Zakan_B_Std_MidAir1_upper");
	m_flyTime = 3.f;
}

void ZakanAir::UpdateState()
{

	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_MidAir1_upper")
	{
		if (m_animController->GetPlayRemainTime() < 0.2f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			m_animController->PlayBlending("Zakan_B_Std_MidAir1_lower");
		}
	}
	else
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"rise");
			return;
		}
	}
}

void ZakanAir::ExitState()
{
}
