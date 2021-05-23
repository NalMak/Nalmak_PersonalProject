#include "stdafx.h"
#include "LynFly.h"


LynFly::LynFly()
{
}


LynFly::~LynFly()
{
}

void LynFly::Initialize()
{
}

void LynFly::EnterState()
{
	m_info->StartSkill();
	m_info->m_gravityPower = 0.f;
	m_info->SetSpeed(8.f);
	m_character->SetVelocityY(-3.f);
	m_animController->PlayBlending("Lyn_P_Std_Mov_Glide_Front_Start");
}

void LynFly::UpdateState()
{
	if (m_character->IsGround())
	{
		m_animController->SetBlendOption(0.1f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"land");
		return;
	}

	/*if (!m_animController->IsPlay("Lyn_P_Std_Mov_Glide_Front_Start"))
	{
		m_animController->PlayBlending("Lyn_P_Std_Mov_Glide_Front_Boost");
		m_info->SetSpeed(10.f);

	}*/
	
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		SetState(L"fall");
		return;
	}
}

void LynFly::ExitState()
{
	m_info->m_gravityPower = 55.f;
	m_character->SetVelocityY(0.f);

	m_info->EndSkill();
}
