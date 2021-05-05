#include "stdafx.h"
#include "LynBaldo.h"


LynBaldo::LynBaldo()
{
}


LynBaldo::~LynBaldo()
{
}

void LynBaldo::Initialize()
{
}

void LynBaldo::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Hide_Baldo0");
}

void LynBaldo::UpdateState()
{
	
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Hide_Baldo0")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Hide_Baldo1");
		}
	}
	else
	{
		if (!m_animController->IsPlay())
		{
			//SetInteger(L"IsBlend", 1);
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
	
}

void LynBaldo::ExitState()
{
	m_info->UpdateWeapon(LYN_STATE_BATTLE_HIDEBLADE);
	m_info->EndSkill();
}
