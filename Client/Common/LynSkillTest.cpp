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
	m_animController->Play("Lyn_B_Hide_BattoCombo2_Exec");
}

void LynSkillTest::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_BattoCombo2_Exec")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Hide_BattoCombo2_Swing");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_BattoCombo2_Swing")
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"idle");
			return;
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_SwordFlash_End")
	{
		if (!m_animController->IsPlay())
		{
			SetState(L"idle");
			return;
		}
	}

	
}

void LynSkillTest::ExitState()
{
}
