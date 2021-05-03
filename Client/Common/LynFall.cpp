#include "stdafx.h"
#include "LynFall.h"


LynFall::LynFall()
{
}


LynFall::~LynFall()
{
}

void LynFall::Initialize()
{
}

void LynFall::EnterState()
{
	m_lynMoveControl->SetSpeed(m_info->m_airSpeed);


	auto dir = m_lynMoveControl->UpdateDirection();

	string anim = "";
	switch (dir)
	{
	case LYN_MOVE_DIR_STATE_FRONT:
	case LYN_MOVE_DIR_STATE_BACK:
	case LYN_MOVE_DIR_STATE_NONE:
		anim = "Mov_JumpFront";
		break;
	case LYN_MOVE_DIR_STATE_RIGHT:
	case LYN_MOVE_DIR_STATE_FRONTRIGHT:
	case LYN_MOVE_DIR_STATE_BACKRIGHT:
		anim = "Mov_JumpRight";
		break;
	case LYN_MOVE_DIR_STATE_LEFT:
	case LYN_MOVE_DIR_STATE_FRONTLEFT:
	case LYN_MOVE_DIR_STATE_BACKLEFT:
		anim = "Mov_JumpLeft";
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
	m_animController_lower->Play(anim);
}

void LynFall::UpdateState()
{
	m_lynMoveControl->UpdatePosition();

	if (m_info->m_animFixPart.Check(ANIMATION_FIX_PART_LOWER))
		return;

	if (m_character->IsGround())
	{
		SetState(L"move");
		return;
	}
	m_character->AddVelocity(0, -30 * dTime, 0);

}

void LynFall::ExitState()
{
}
