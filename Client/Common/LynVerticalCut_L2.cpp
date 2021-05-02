#include "stdafx.h"
#include "LynVerticalCut_L2.h"


LynVerticalCut_L2::LynVerticalCut_L2()
{
}


LynVerticalCut_L2::~LynVerticalCut_L2()
{
}

void LynVerticalCut_L2::Initialize()
{
}

void LynVerticalCut_L2::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


	m_animController_upper->Play("Lyb_B_Std_VerticalCul_01_3");


}

void LynVerticalCut_L2::UpdateState()
{
	if (m_animController_upper->GetPlayRemainTime() < 0.35f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			SetState(L"verticalCut_r2");
			return;
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynVerticalCut_L2::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);


}
