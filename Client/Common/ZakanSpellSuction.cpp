#include "stdafx.h"
#include "ZakanSpellSuction.h"


ZakanSpellSuction::ZakanSpellSuction()
{
}


ZakanSpellSuction::~ZakanSpellSuction()
{
}

void ZakanSpellSuction::Initialize()
{
}

void ZakanSpellSuction::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);

	m_animController->Play("Zakan_SpellSuction_Cast");
}

void ZakanSpellSuction::UpdateState()
{
	if (!m_animController->IsPlay("Zakan_SpellSuction_Cast"))
	{
		m_animController->Play("Zakan_SpellSuction_Exec_Loop");
	}
	if (!m_animController->IsPlay("Zakan_SpellSuction_Exec_Loop"))
	{
		m_animController->Play("Zakan_SpellSuction_Exec_End");
	}
	if (!m_animController->IsPlay("Zakan_SpellSuction_Exec_End"))
	{



		SetState(L"battle_idle");
		return;
	}
}

void ZakanSpellSuction::ExitState()
{
}

