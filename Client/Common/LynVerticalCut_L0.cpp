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
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController_upper->Play("Lyb_B_Std_VerticalCul_01_1");

	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);



}

void LynVerticalCut_L0::UpdateState()
{
	if (m_animController_upper->IsOverTime(0.5f))
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

	if (!m_animController_upper->IsPlay())
	{
		SetState(L"verticalCut_l1");
	}
}

void LynVerticalCut_L0::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);

}
