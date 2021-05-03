#include "stdafx.h"
#include "LynJump.h"


LynJump::LynJump()
{
}


LynJump::~LynJump()
{
}

void LynJump::Initialize()
{
}

void LynJump::EnterState()
{
	m_lynControl->SetSpeed(m_info->m_airSpeed);
}

void LynJump::UpdateState()
{
}

void LynJump::ExitState()
{
}
