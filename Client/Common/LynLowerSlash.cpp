#include "stdafx.h"
#include "LynLowerSlash.h"


LynLowerSlash::LynLowerSlash()
{
}


LynLowerSlash::~LynLowerSlash()
{
}

void LynLowerSlash::Initialize()
{

}

void LynLowerSlash::EnterState()
{
	m_info->StartSkill();
	m_info->UpdateWeapon(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_lowerSlash1");
}

void LynLowerSlash::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"lowerSlash2");
		return;
	}
}

void LynLowerSlash::ExitState()
{
	m_info->EndSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
}
