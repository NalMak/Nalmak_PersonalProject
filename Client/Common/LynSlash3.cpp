#include "stdafx.h"
#include "LynSlash3.h"


LynSlash3::LynSlash3()
{
}

LynSlash3::~LynSlash3()
{
}

void LynSlash3::Initialize()
{
}

void LynSlash3::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash3");



	m_isCombo = false;
}

void LynSlash3::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.3)
		{
			m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash1");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.3)
		{
			m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}

	
}

void LynSlash3::ExitState()
{
	m_info->EndSkill();
}
