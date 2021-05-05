#include "stdafx.h"
#include "LynLand.h"


LynLand::LynLand()
{
}


LynLand::~LynLand()
{
}

void LynLand::Initialize()
{
}

void LynLand::EnterState()
{

	//string anim = "Mov_JumpToIdle";

	//if (dir != LYN_MOVE_DIR_STATE_NONE)
	//{
	//	SetState(L"move");
	//	return;
	//}
	//switch (m_info->m_state)
	//{
	//case LYN_STATE_PEACE_STANDARD:
	//	anim = "Lyn_P_Std_" + anim;
	//	break;
	//case LYN_STATE_BATTLE_STANDARD:
	//	anim = "Lyn_B_Std_" + anim;
	//	break;
	//case LYN_STATE_BATTLE_HIDEBLADE:
	//	anim = "Lyn_B_Hide_" + anim;
	//	break;
	//default:
	//	break;
	//}
	//
	//m_animController_lower->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	//m_animController_lower->PlayBlending(anim);
}

void LynLand::UpdateState()
{
	m_character->SetVelocity(0, 0, 0);
	
	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}

}

void LynLand::ExitState()
{
}
