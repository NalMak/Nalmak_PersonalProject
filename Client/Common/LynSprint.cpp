#include "stdafx.h"
#include "LynSprint.h"


LynSprint::LynSprint()
{
}


LynSprint::~LynSprint()
{
}

void LynSprint::Initialize()
{
}

void LynSprint::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_sprintSpeed);
	m_animController->PlayBlending("Lyn_P_Std_Mov_Sprint_JumpFront");
}

void LynSprint::UpdateState()
{
	if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		SetState(L"idle");
		return;
	}
}

void LynSprint::ExitState()
{
	m_info->EndSkill();
}
