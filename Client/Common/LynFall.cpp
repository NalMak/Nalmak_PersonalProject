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

	m_lynControl->SetSpeed(m_info->m_airSpeed);


	auto dir = m_lynControl->UpdateDirection();

	string anim = "";
	switch (dir)
	{
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONT:
	case LynStateControl::LYN_MOVE_DIR_STATE_BACK:
	case LynStateControl::LYN_MOVE_DIR_STATE_NONE:
		anim = "Mov_JumpFront";
		break;
	case LynStateControl::LYN_MOVE_DIR_STATE_RIGHT:
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONTRIGHT:
	case LynStateControl::LYN_MOVE_DIR_STATE_BACKRIGHT:
		anim = "Mov_JumpRight";
		break;
	case LynStateControl::LYN_MOVE_DIR_STATE_LEFT:
	case LynStateControl::LYN_MOVE_DIR_STATE_FRONTLEFT:
	case LynStateControl::LYN_MOVE_DIR_STATE_BACKLEFT:
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
	m_animController_lower->PlayBlending(anim);
}

void LynFall::UpdateState()
{
	m_lynControl->UpdatePosition();

	if (m_character->IsGround())
	{
		SetState(L"land");
		return;
	}
	m_character->AddVelocity(0, -30 * dTime, 0);

}

void LynFall::ExitState()
{
}
