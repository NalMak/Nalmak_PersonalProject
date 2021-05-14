#include "stdafx.h"
#include "LynEventIdle.h"


LynEventIdle::LynEventIdle()
{
}


LynEventIdle::~LynEventIdle()
{
}

void LynEventIdle::Initialize()
{
}

void LynEventIdle::EnterState()
{
	m_bnsMainCam->UnLockTarget();

	string anim = "Lyn_P_Std_Idle_Event";

	m_animIdex = 1;
	string strNum = to_string(m_animIdex);

	m_animController->SetBlendOption(1.f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	m_animController->PlayBlending(anim + strNum);
	++m_animIdex;
	m_animController->SetRootMotion(false);
}

void LynEventIdle::UpdateState()
{
	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE)
	{
		SetState(L"idle");
		return;
	}

	if (m_animController->GetPlayRemainTime() < 1.f)
	{
		m_animController->SetBlendOption(1.f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

		string anim = "Lyn_P_Std_Idle_Event";

		string strNum = to_string(m_animIdex);

		m_animController->PlayBlending(anim + strNum);
		++m_animIdex;

		if (m_animIdex > 6)
			m_animIdex = 1;
	}
}

void LynEventIdle::ExitState()
{
	m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

	m_bnsMainCam->LockTarget();
	m_animController->SetRootMotion(true);

}
