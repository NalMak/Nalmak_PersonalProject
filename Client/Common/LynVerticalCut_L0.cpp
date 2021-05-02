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


	BoxCollider::Desc box;
	box.height = 2;
	box.depth = 2;
	box.height = 2;
	box.isTrigger = true;
	INSTANTIATE(OBJECT_TAG_PLAYER,OBJECT_LAYER_NAVIMESH,L"vertical")->AddComponent<BoxCollider>(&box)->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 3.f + Vector3(0, 1.5f, 0));
}

void LynVerticalCut_L0::UpdateState()
{
	if (!m_animController_upper->IsPlay())
	{
		SetState(L"verticalCut_l1");
	}
}

void LynVerticalCut_L0::ExitState()
{
	m_info->m_animFixPart.Off(ANIMATION_FIX_PART_UPPER);

}
