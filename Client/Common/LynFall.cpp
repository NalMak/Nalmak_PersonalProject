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
	m_info->SetSpeed(m_info->m_airSpeed);

	auto dir = (LYN_MOVE_DIR_STATE)GetInteger(L"JumpDirection");

	string anim = "";
	switch (dir)
	{
	case LYN_MOVE_DIR_STATE_FRONT:
		anim = "Mov_JumpFront";
		break;
	case LYN_MOVE_DIR_STATE_RIGHT:
		anim = "Mov_JumpRight";
		break;
	case LYN_MOVE_DIR_STATE_LEFT:
		anim = "Mov_JumpLeft";
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

void LynFall::UpdateState()
{
	if (m_character->IsGround())
	{
		SetState(L"land");
		return;
	}
}

void LynFall::ExitState()
{
	m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
}
