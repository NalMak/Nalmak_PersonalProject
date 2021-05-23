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

	if (GetInteger(L"extension") == 0)
	{
		m_animController->Play("Zakan_B_Std_MidAir1_upper");
	}
	m_flyTime = GetFloat(L"ccTime");
}

void ZakanAir::UpdateState()
{

	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_MidAir1_upper")
	{

		if (m_animController->GetPlayRemainTime() < 1.f)
		{
			m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			m_animController->PlayBlending("Zakan_B_Std_MidAir1_idle");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_MidAir1_idle")
	{
		m_flyTime -= dTime;

		if (m_flyTime < 0)
		{
			m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
			m_animController->PlayBlending("Zakan_B_Std_MidAir1_lower");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Std_MidAir1_lower")
	{

		if(m_animController->GetPlayRemainTime() < 0.2f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"rise");
			return;
		}
	}
}

void ZakanAir::ExitState()
{
}
