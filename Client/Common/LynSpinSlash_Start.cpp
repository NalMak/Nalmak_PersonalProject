#include "stdafx.h"
#include "LynSpinSlash_Start.h"


LynSpinSlash_Start::LynSpinSlash_Start()
{
}


LynSpinSlash_Start::~LynSpinSlash_Start()
{
}

void LynSpinSlash_Start::Initialize()
{
}

void LynSpinSlash_Start::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyn_B_Std_SpinSlash_01");
	m_animController_lower->Play("Lyn_B_Std_SpinSlash_01");
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);

}

void LynSpinSlash_Start::UpdateState()
{
	if (!m_animController_upper->IsPlay())
	{
		
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_TAB))
		{
			SetState(L"spinSlash_combo");
			return;
		}
		else
		{
			SetState(L"spinSlash_end");
			return;
		}
	}
}

void LynSpinSlash_Start::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_LOWER);

	m_animController_upper->SetSeparate(true);
	m_animController_lower->SetActive(true);//->Play("Lyn_B_Std_SpinSlash_01_1");

	SetInteger(L"IsBlend", 0);
}
