#include "stdafx.h"
#include "LynVerticalCut_L0.h"

LynVerticalCut_L0::LynVerticalCut_L0()
{
}


LynVerticalCut_L0::~LynVerticalCut_L0()
{
}

void LynVerticalCut_L0::Initialize()
{

}

void LynVerticalCut_L0::EnterState()
{
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_01_1");

	ReduceInnerPower(2);

}

void LynVerticalCut_L0::UpdateState()
{
	if (m_animController->IsOverTime(0.5f))
	{
		/*auto shake = Core::GetInstance()->GetMainCamera()->GetComponent<CameraShake>();
		if (shake)
		{
			shake->Shake(3.f, 5.f, 5, 0.2f, 10, { 1,1,0 });
		}*/
		AttackInfo::Desc attack;
		attack.height = 7;
		attack.depth = 10;
		attack.width = 4;
		CreateAttackInfo(&attack,6.f,1.5f,3.f);
	
	}

	if (!m_animController->IsPlay())
	{
		SetState(L"verticalCut_l1");
	}
}

void LynVerticalCut_L0::ExitState()
{
	m_info->EndSkill();

}
