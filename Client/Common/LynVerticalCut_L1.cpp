#include "stdafx.h"
#include "LynVerticalCut_L1.h"


LynVerticalCut_L1::LynVerticalCut_L1()
{
}


LynVerticalCut_L1::~LynVerticalCut_L1()
{
}

void LynVerticalCut_L1::Initialize()
{
}

void LynVerticalCut_L1::EnterState()
{
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_01_2");

}

void LynVerticalCut_L1::UpdateState()
{
	if (m_animController_upper->GetPlayRemainTime() < 0.2f)
	{
		m_animController_upper->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			SetState(L"verticalCut_r2");
			return;
		}
		else
		{
			SetState(L"wait");
			return;
		}
	}
}

void LynVerticalCut_L1::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);

}
