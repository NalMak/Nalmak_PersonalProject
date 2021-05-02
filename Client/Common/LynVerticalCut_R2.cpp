#include "stdafx.h"
#include "LynVerticalCut_R2.h"


LynVerticalCut_R2::LynVerticalCut_R2()
{
}


LynVerticalCut_R2::~LynVerticalCut_R2()
{
}

void LynVerticalCut_R2::Initialize()
{
}

void LynVerticalCut_R2::EnterState()
{
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_02_3");
}

void LynVerticalCut_R2::UpdateState()
{
	if (m_animController_upper->GetPlayRemainTime() < 0.35f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			SetState(L"verticalCut_l2");
			return;
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynVerticalCut_R2::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);

}
