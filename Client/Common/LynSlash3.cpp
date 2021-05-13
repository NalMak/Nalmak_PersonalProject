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
	m_info->SetSpeed(m_info->m_airSpeed * 0.5f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash3");

	m_isCombo = false;

	AttackInfo::Desc attack;
	attack.height = 5;
	attack.depth = 5;
	attack.width = 8;
	attack.innerPower = 2;
	CreateAttackInfo(&attack, 3.f, 1.5f, 1.3f);
}

void LynSlash3::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.6f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.4)
		{
			m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash1");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.4)
		{
			m_animController->SetBlendOption(0.4f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}

	
}

void LynSlash3::ExitState()
{
	m_info->EndSkill();
}
