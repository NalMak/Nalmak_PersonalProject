#include "stdafx.h"
#include "LynSkillTest.h"


LynSkillTest::LynSkillTest()
{
}


LynSkillTest::~LynSkillTest()
{
}

void LynSkillTest::Initialize()
{
}

void LynSkillTest::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyn_B_Hide_SwordFlash_Swing");
	m_animController_lower->Play("Lyn_B_Hide_SwordFlash_Swing");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_LOWER);

}

void LynSkillTest::UpdateState()
{
	if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Swing")
	{
		if (!m_animController_upper->IsPlay())
		{
			m_animController_upper->Play("Lyn_B_Hide_SwordFlash_Exec");
			m_animController_lower->Play("Lyn_B_Hide_SwordFlash_Exec");
		}
	}
	else if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_Exec")
	{
		if (!m_animController_upper->IsPlay())
		{

			m_animController_upper->Play("Lyn_B_Hide_SwordFlash_End");
			m_animController_lower->Play("Lyn_B_Hide_SwordFlash_End");
		}
	}
	else if (m_animController_upper->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_End")
	{
		if (!m_animController_upper->IsPlay())
		{
			SetState(L"wait");
			return;
		}
	}

	
}

void LynSkillTest::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_LOWER);
}
