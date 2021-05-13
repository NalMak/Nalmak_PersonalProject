#include "stdafx.h"
#include "LynSlash2.h"


LynSlash2::LynSlash2()
{
}

LynSlash2::~LynSlash2()
{
}

void LynSlash2::Initialize()
{
	
}

void LynSlash2::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(m_info->m_airSpeed * 0.8f);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_defaultSlash2");



	m_isCombo = false;

	AttackInfo::Desc attack;
	attack.height = 5;
	attack.depth = 5;
	attack.width = 8;
	attack.innerPower = 1;
	CreateAttackInfo(&attack, 3.f, 1.5f, 1.f);
}

void LynSlash2::UpdateState()
{
	if (BETWEEN(m_animController->GetPlayRemainTime(), 0.9f, 1.2f))
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			m_isCombo = true;
		}
	}
	

	if (m_isCombo)
	{
		if (m_animController->GetPlayRemainTime() < 0.9f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"slash3");
			return;
		}
	}
	else
	{
		if (m_animController->GetPlayRemainTime() < 0.6f)
		{
			m_animController->SetBlendOption(0.6f, 1.f, D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
}

void LynSlash2::ExitState()
{
	m_info->EndSkill();
}
