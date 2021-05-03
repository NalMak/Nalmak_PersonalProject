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
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_02_1");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


}

void LynVerticalCut_R0::UpdateState()
{
	if (m_animController_upper->IsOverTime(0.5f))
	{
		AttackInfo::Desc attack;
		attack.height = 4;
		attack.depth = 8;
		attack.width = 2;
		INSTANTIATE(OBJECT_TAG_PLAYER, OBJECT_LAYER_NAVIMESH, L"vertical")
			->AddComponent<AttackInfo>()
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 4.f + Vector3(0, 1.5f, 0))
			->SetRotation(m_transform->GetWorldRotation());
	}

	if (!m_animController_upper->IsPlay())
	{
		
		SetState(L"verticalCut_r1");
	}
}

void LynVerticalCut_R0::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);


}
