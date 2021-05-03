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
	m_animController_upper->PlayBlending("Lyn_P_BtoP_2");
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


}

void LynBattleToPeace::UpdateState()
{
	if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_P_BtoP_2")
	{
		if (m_animController_upper->GetPlayRemainTime() < 1.4f)
		{
			m_info->m_state = LYN_STATE_PEACE_STANDARD;
		}
		if (!m_animController_upper->IsPlay())
		{
			m_animController_upper->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		/*	return;
			m_animController_upper->Play("Lyn_P_BtoP_2");*/
		}
	}
	
}

void LynBattleToPeace::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);

	//m_info->SetState(LYN_STATE_PEACE_STANDARD);
}
