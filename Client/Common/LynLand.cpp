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
	auto dir = m_lynControl->UpdateDirection();

	string anim = "";
	switch (dir)
	{
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONT:
	case LynStateControl::LYN_MOVE_DIR_STATE_NONE:
		anim = "Mov_JumpToMove_Front";
		break;
	case LynStateControl::LYN_MOVE_DIR_STATE_RIGHT:
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONTRIGHT:
	case LynStateControl::LYN_MOVE_DIR_STATE_BACKRIGHT:
		anim = "Mov_JumpToMove_Right";
		break;
	case LynStateControl::LYN_MOVE_DIR_STATE_LEFT:
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONTLEFT:
	case LynStateControl::LYN_MOVE_DIR_STATE_BACKLEFT:
		anim = "Mov_JumpToMove_Left";
		break;
	case LynStateControl::LYN_MOVE_DIR_STATE_BACK:
		anim = "Mov_JumpToMove_Back";
		break;
	default:
		break;
	}

	switch (m_info->m_state)
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
	m_animController_lower->PlayBlending(anim);
}

void LynLand::UpdateState()
{
	if (m_animController_lower->GetPlayRemainTime() < 0.2f)
	{
		SetState(L"move");
		return;
	}
}

void LynLand::ExitState()
{
}
