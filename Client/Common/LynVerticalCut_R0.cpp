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
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_02_1");


}

void LynVerticalCut_R0::UpdateState()
{
	if (m_animController->IsOverTime(0.5f))
	{
		AttackInfo::Desc attack;
		attack.height = 12;
		attack.depth = 20;
		attack.width = 6;
		INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
			->AddComponent<AttackInfo>()
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 6.f + Vector3(0, 1.5f, 0))
			->SetRotation(m_transform->GetWorldRotation());
	}

	if (!m_animController->IsPlay())
	{
		
		SetState(L"verticalCut_r1");
	}
}

void LynVerticalCut_R0::ExitState()
{
	m_info->EndSkill();
	SetInteger(L"IsBlend", 1);
}
