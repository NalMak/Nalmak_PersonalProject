#include "stdafx.h"
#include "LynSpinSlash_Combo.h"


LynSpinSlash_Combo::LynSpinSlash_Combo()
{
}

LynSpinSlash_Combo::~LynSpinSlash_Combo()
{
}

void LynSpinSlash_Combo::Initialize()
{
}

void LynSpinSlash_Combo::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);

	m_animController_upper->Play("Lyn_B_Std_SpinSlash_01_1");
	m_animController_lower->Play("Lyn_B_Std_SpinSlash_01_1");


	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);

}

void LynSpinSlash_Combo::UpdateState()
{
	if (m_animController_upper->GetPlayRemainTime() < 0.2f)
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

void LynSpinSlash_Combo::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_LOWER);

}
