#include "stdafx.h"
#include "LynSlash1.h"


LynSlash1::LynSlash1()
{
}


LynSlash1::~LynSlash1()
{
}

void LynSlash1::Initialize()
{
}

void LynSlash1::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash1");
	m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,2.f,0 }, 0.4f, { 0,0 }, { 0.5f,1 }, { 1,1 }, { 1,0.f });

	m_isCombo = false;

}

void LynSlash1::UpdateState()
{
	/*if (m_animController->IsOverTime(0.3f))
	{
		m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,-0.5f,0 }, 0.2f, { 0,0 }, { 0,1 }, { 1,1 }, { 1,0.f });
	}*/
	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}

	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.3f)
		{
			m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_LINEAR);
			SetInteger(L"IsBlend", 1);
			SetState(L"slash2");
			return;
		}
	}
	else
	{
		if (!m_animController->IsPlay())
		{
			SetInteger(L"IsBlend", 0);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash1::ExitState()
{
	m_info->EndSkill();
}
