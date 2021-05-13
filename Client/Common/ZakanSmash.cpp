#include "stdafx.h"
#include "ZakanSmash.h"


ZakanSmash::ZakanSmash()
{
}


ZakanSmash::~ZakanSmash()
{
}

void ZakanSmash::Initialize()
{
}

void ZakanSmash::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_WEAK);

	m_info->LookTarget();
	m_animController->Play("Zakan_B_Spell_Skl_Smash_Cast");
}

void ZakanSmash::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Skl_Smash_Exec1");
			return;
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Exec1")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Skl_Smash_Exec2");
			return;
		}

	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Exec2")
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanSmash::ExitState()
{
}
