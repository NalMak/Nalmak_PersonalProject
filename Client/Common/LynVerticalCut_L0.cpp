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

	m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,-0.7f,0 }, 0.6f, { 0,0 }, { 0.0f,1.f }, { 0.52f,0.75f }, { 1,0 });


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
		SetState(L"verticalCut_l1");
	}
}

void LynVerticalCut_L0::ExitState()
{
	m_info->EndSkill();
	SetInteger(L"IsBlend", 1);

}
