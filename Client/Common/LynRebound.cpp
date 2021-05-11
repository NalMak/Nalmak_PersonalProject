#include "stdafx.h"
#include "LynRebound.h"


LynRebound::LynRebound()
{
}


LynRebound::~LynRebound()
{
}

void LynRebound::Initialize()
{
}

void LynRebound::EnterState()
{
	string animName = "";
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		animName = "Mov_LeftToRight";
		m_isRight = true;
	}
	else
	{
		animName = "Mov_RightToLeft";
		m_isRight = false;
	}

	auto state = m_info->GetState();
	switch (state)
	{
	case LYN_STATE_PEACE_STANDARD:
		animName = "Lyn_P_Std_" + animName;
		break;
	case LYN_STATE_BATTLE_STANDARD:
		animName = "Lyn_B_Std_" + animName;
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		animName = "Lyn_B_Hide_" + animName;
		break;
	default:
		break;
	}
	m_animController->PlayBlending(animName);

}

void LynRebound::UpdateState()
{
	if (m_isRight)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
		{
			SetState(L"rebound");
			return;
		}
	}
	else
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
		{
			SetState(L"rebound");
			return;
		}
	}

	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"move");
		return;
	}
}

void LynRebound::ExitState()
{
}
