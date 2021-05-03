#include "stdafx.h"
#include "LynVerticalCut_L2.h"


LynVerticalCut_L2::LynVerticalCut_L2()
{
}


LynVerticalCut_L2::~LynVerticalCut_L2()
{
}

void LynVerticalCut_L2::Initialize()
{
}

void LynVerticalCut_L2::EnterState()
{
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_info->m_animFixPart.On(ANIMATION_FIX_PART_UPPER);


	m_animController_upper->Play("Lyb_B_Std_VerticalCul_01_3");


}

void LynVerticalCut_L2::UpdateState()
{
	if (m_animController_upper->IsOverTime(0.2f))
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

	if (m_animController_upper->GetPlayRemainTime() < 0.35f)
	{
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

void LynVerticalCut_L2::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);
	SetInteger(L"IsBlend", 1);


}
