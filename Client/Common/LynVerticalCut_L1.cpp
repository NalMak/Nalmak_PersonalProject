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
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_01_2");

}

void LynVerticalCut_L1::UpdateState()
{
	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE && !m_isUpper)
	{
		SetState(L"move");
		return;
	}
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
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

void LynVerticalCut_L1::ExitState()
{
	m_info->EndSkill();
}
