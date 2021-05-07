#include "stdafx.h"
#include "LynBattleToPeace.h"


LynBattleToPeace::LynBattleToPeace()
{
}


LynBattleToPeace::~LynBattleToPeace()
{
}

void LynBattleToPeace::Initialize()
{
}

void LynBattleToPeace::EnterState()
{
	m_animController->PlayBlending("Lyn_P_BtoP_1");
}

void LynBattleToPeace::UpdateState()
{
	
	if (m_animController->GetPlayRemainTime() < 0.8f)
	{
		m_info->SetState(LYN_STATE_PEACE_STANDARD);
	}
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
	
}

void LynBattleToPeace::ExitState()
{
	SetInteger(L"IsBlend", 1);
}
