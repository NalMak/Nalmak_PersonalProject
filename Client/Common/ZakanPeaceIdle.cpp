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

	m_info->LostTarget();
}

void ZakanPeaceIdle::UpdateState()
{
	if (m_info->GetTarget())
	{
		SetState(L"NATK1");
		return;
	}
}

void ZakanPeaceIdle::ExitState()
{
}
