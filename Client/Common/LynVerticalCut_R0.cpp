#include "stdafx.h"
#include "LynVerticalCut_R0.h"


LynVerticalCut_R0::LynVerticalCut_R0()
{
}


LynVerticalCut_R0::~LynVerticalCut_R0()
{
}

void LynVerticalCut_R0::Initialize()
{
}

void LynVerticalCut_R0::EnterState()
{
		

	ReduceInnerPower(2);
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_02_1");


	int index = Nalmak_Math::Rand(1, 4);
	VoicePlay(L"FemaleChild01_PreAtk1_0" + to_wstring(index));
}

void LynVerticalCut_R0::UpdateState()
{
	if (m_animController->IsOverTime(0.5f))
	{
		/*auto shake = Core::GetInstance()->GetMainCamera()->GetComponent<CameraShake>();
		if (shake)
		{
			shake->Shake(3.f, 5.f, 5, 0.2f, 10, { -1,1,0 });

		}*/
		AttackInfo::Desc attack;
		attack.height = 7;
		attack.depth = 10;
		attack.width = 4;
		CreateAttackInfo(&attack, 6.f, 1.5f, 3.f);
	}

	if (!m_animController->IsPlay())
	{
		
		SetState(L"verticalCut_r1");
	}
}

void LynVerticalCut_R0::ExitState()
{
	m_info->EndSkill();
}
