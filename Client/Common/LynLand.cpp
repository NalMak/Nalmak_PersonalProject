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
	string anim;

	auto dirState = m_info->GetDirectionState();
	switch (dirState)
	{
	case LYN_MOVE_DIR_STATE_FRONT:
		anim = "Mov_JumpToMove_Front";
		break;
	case LYN_MOVE_DIR_STATE_RIGHT:
		anim = "Mov_JumpToMove_Right";
		break;
	case LYN_MOVE_DIR_STATE_FRONTRIGHT:
		anim = "Mov_JumpToMove_Right";
		break;
	case LYN_MOVE_DIR_STATE_LEFT:
		anim = "Mov_JumpToMove_Left";
		break;
	case LYN_MOVE_DIR_STATE_FRONTLEFT:
		anim = "Mov_JumpToMove_Left";
		break;
	case LYN_MOVE_DIR_STATE_BACK:
		anim = "Mov_JumpToMove_Back";
		break;
	case LYN_MOVE_DIR_STATE_BACKRIGHT:
		anim = "Mov_JumpToMove_Right";
		break;
	case LYN_MOVE_DIR_STATE_BACKLEFT:
		anim = "Mov_JumpToMove_Left";
		break;
	case LYN_MOVE_DIR_STATE_NONE:
		anim = "Mov_JumpToIdle";
		break;
	default:
		break;
	}


	switch (m_info->GetState())
	{
	case LYN_STATE_PEACE_STANDARD:
		anim = "Lyn_P_Std_" + anim;
		break;
	case LYN_STATE_BATTLE_STANDARD:
		anim = "Lyn_B_Std_" + anim;
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		anim = "Lyn_B_Hide_" + anim;
		break;
	default:
		break;
	}

	m_animController->PlayBlending(anim);
}

void LynLand::UpdateState()
{
	
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}

}

void LynLand::ExitState()
{
	
}
