#include "stdafx.h"
#include "ZakanBattleIdle.h"


ZakanBattleIdle::ZakanBattleIdle()
{
}


ZakanBattleIdle::~ZakanBattleIdle()
{
}

void ZakanBattleIdle::Initialize()
{
}

void ZakanBattleIdle::EnterState()
{

	m_character->SetVelocityX(0);
	m_character->SetVelocityZ(0);

	if (m_info->GetDistanceToTarget() < 6.f)
	{
		SetState(L"pattern");
		return;
	}
	else if (BETWEEN(m_info->GetDistanceToTarget(),6,16))
	{
		SetState(L"move");
		return;
	}
	else if (BETWEEN(m_info->GetDistanceToTarget(), 16, 50))
	{
		SetState(L"teleport");
		return;
	}
	//m_animController->PlayBlending("Zakan_B_None_Mov_Idle");
	

}

void ZakanBattleIdle::UpdateState()
{
	
	
}

void ZakanBattleIdle::ExitState()
{
}
