#include "stdafx.h"
#include "ZakanRise.h"


ZakanRise::ZakanRise()
{
}


ZakanRise::~ZakanRise()
{
}

void ZakanRise::Initialize()
{
}

void ZakanRise::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_animController->Play("Zakan_B_Std_Down_Front_End");
}

void ZakanRise::UpdateState()
{
	if (!m_animController->IsPlay())
	{
		SetState(L"battle_idle");
		return;
	}
}

void ZakanRise::ExitState()
{
}
