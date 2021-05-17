#include "stdafx.h"
#include "ZakanDead.h"
#include "LynInfo.h"


ZakanDead::ZakanDead()
{
}


ZakanDead::~ZakanDead()
{
}

void ZakanDead::Initialize()
{
}

void ZakanDead::EnterState()
{
	m_animController->Play("Zakan_B_Std_Down_Start");
	m_info->SetBattleState(BATTLE_STATE_DEAD);
	m_gameObject->DeleteComponent<CharacterController>();
}

void ZakanDead::UpdateState()
{
	if (!m_animController->IsPlay("Zakan_B_Std_Down_Start"))
	{
		m_animController->Play("Zakan_B_Std_Down_Looping");
	}
}

void ZakanDead::ExitState()
{
}
