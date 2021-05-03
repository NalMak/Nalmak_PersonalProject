#include "stdafx.h"
#include "LynVerticalCut_R1.h"


LynVerticalCut_R1::LynVerticalCut_R1()
{
}


LynVerticalCut_R1::~LynVerticalCut_R1()
{
}

void LynVerticalCut_R1::Initialize()
{
}

void LynVerticalCut_R1::EnterState()
{
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_02_2");

}

void LynVerticalCut_R1::UpdateState()
{
	
	if (m_animController_upper->GetPlayRemainTime() < 0.1f)
	{
		

		m_animController_upper->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	
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

void LynVerticalCut_R1::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);


}
