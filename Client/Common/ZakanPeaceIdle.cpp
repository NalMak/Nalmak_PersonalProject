#include "stdafx.h"
#include "ZakanPeaceIdle.h"


ZakanPeaceIdle::ZakanPeaceIdle()
{
}


ZakanPeaceIdle::~ZakanPeaceIdle()
{
}

void ZakanPeaceIdle::Initialize()
{
	m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
}

void ZakanPeaceIdle::EnterState()
{
	m_animController->PlayBlending("Zakan_P_Std_Mov_Idle");
	m_transform->rotation = m_info->GetSpawnRot();
	
	m_character->SetVelocityX(0);
	m_character->SetVelocityZ(0);
}

void ZakanPeaceIdle::UpdateState()
{
	if (m_info->GetTarget())
	{
		SetState(L"battle_idle");
		return;
	}
}

void ZakanPeaceIdle::ExitState()
{
}