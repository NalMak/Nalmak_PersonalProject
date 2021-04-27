#include "stdafx.h"
#include "LynJumpToIdle.h"


LynJumpToIdle::LynJumpToIdle()
{
}


LynJumpToIdle::~LynJumpToIdle()
{
}

void LynJumpToIdle::Initialize()
{
}

void LynJumpToIdle::EnterState()
{

	m_animController->Play("Lyn_P_Std_Mov_JumpToIdle");
}

void LynJumpToIdle::UpdateState()
{
	/*float ratio = abs(m_animController->GetPlayRatio() * 2 - 1);
	
	m_height = Nalmak_Math::Lerp(  m_info->m_jumpHalfHeight, m_info->m_halfHeight, ratio);
	m_height = Nalmak_Math::Clamp(m_height, m_info->m_jumpHalfHeight, m_info->m_halfHeight);
	m_character->SetHalfHeight(m_height);


	*/
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		SetState(L"idle");
		return;
	}
}

void LynJumpToIdle::ExitState()
{
	/*m_height = m_info->m_halfHeight;
	m_character->SetHalfHeight(m_height);*/
}
