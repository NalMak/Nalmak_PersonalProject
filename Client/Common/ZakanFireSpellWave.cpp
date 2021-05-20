#include "stdafx.h"
#include "ZakanFireSpellWave.h"


ZakanFireSpellWave::ZakanFireSpellWave()
{
}


ZakanFireSpellWave::~ZakanFireSpellWave()
{
}

void ZakanFireSpellWave::Initialize()
{
}

void ZakanFireSpellWave::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);

	m_animController->Play("Zakan_FireSpellWave_Cast");
}

void ZakanFireSpellWave::UpdateState()
{
	if (!m_animController->IsPlay("Zakan_FireSpellWave_Cast"))
	{
		m_animController->Play("Zakan_FireSpellWave_Exec");
	}
	if (!m_animController->IsPlay("Zakan_FireSpellWave_Exec"))
	{
		SetState(L"battle_idle");
		return;
	}
}

void ZakanFireSpellWave::ExitState()
{
}
