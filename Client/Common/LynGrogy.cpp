#include "stdafx.h"
#include "LynGrogy.h"


LynGrogy::LynGrogy()
{
}


LynGrogy::~LynGrogy()
{
}

void LynGrogy::Initialize()
{
}

void LynGrogy::EnterState()
{
	m_info->SetSpeed(0);
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Down_B");
	m_bnsMainCam->UnLockTarget();
}

void LynGrogy::UpdateState()
{
}

void LynGrogy::ExitState()
{
}
