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
	m_character->SetHalfHeight(m_info->m_jumpHalfHeight);

	m_animController->Play("Lyn_P_Std_Mov_JumpToIdle");
	m_height = m_info->m_jumpHalfHeight;
}

void LynJumpToIdle::UpdateState()
{
	float ratio = m_animController->GetPlayRatio();
	float interpolateValue = 0.6f;
	if (ratio > interpolateValue)
	{
		m_height = Nalmak_Math::Lerp(m_height, m_info->m_halfHeight, (ratio - interpolateValue) * 1.2f / interpolateValue);
		m_height = Nalmak_Math::Clamp(m_height, m_info->m_jumpHalfHeight, m_info->m_halfHeight);
		m_character->SetHalfHeight(m_height);
	}


	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		SetState(L"idle");
		return;
	}
}

void LynJumpToIdle::ExitState()
{
	m_height = m_info->m_halfHeight;
	m_character->SetHalfHeight(m_height);
}
