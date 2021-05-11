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
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);

	m_animController->Play("Lyb_B_Std_VerticalCul_01_3");


}

void LynVerticalCut_L2::UpdateState()
{
	if (m_animController->IsOverTime(0.2f))
	{
		/*auto shake = Core::GetInstance()->GetMainCamera()->GetComponent<CameraShake>();
		if (shake)
		{
			shake->Shake(1.f, 2.f, 5, 0.15f, 2, { 1,1,0 });
		}*/

		AttackInfo::Desc attack;
		attack.height = 12;
		attack.depth = 20;
		attack.width = 6;

		INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")

			->AddComponent<AttackInfo>()
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 6.f + Vector3(0, 1.5f, 0))
			->SetRotation(m_transform->GetWorldRotation());
	}

	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE && !m_isUpper)
	{
		SetState(L"move");
		return;
	}

	if (m_animController->GetPlayRemainTime() < 0.35f)
	{
		m_animController->SetBlendOption(0.35f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
			{
				SetState(L"verticalCut_r2");
				return;
			}
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
	m_info->EndSkill();


}
