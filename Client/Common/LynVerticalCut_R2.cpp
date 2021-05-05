#include "stdafx.h"
#include "LynVerticalCut_R2.h"


LynVerticalCut_R2::LynVerticalCut_R2()
{
}


LynVerticalCut_R2::~LynVerticalCut_R2()
{
}

void LynVerticalCut_R2::Initialize()
{
}

void LynVerticalCut_R2::EnterState()
{
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_02_3");
}

void LynVerticalCut_R2::UpdateState()
{
	if (m_animController->IsOverTime(0.2f))
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


	if (m_animController->GetPlayRemainTime() < 0.35f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			SetState(L"verticalCut_l2");
			return;
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynVerticalCut_R2::ExitState()
{
	m_info->EndSkill();
	SetInteger(L"IsBlend", 1);

}
