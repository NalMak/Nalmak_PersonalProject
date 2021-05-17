#include "stdafx.h"
#include "LynKnockBackMiddle.h"


LynKnockBackMiddle::LynKnockBackMiddle()
{
}


LynKnockBackMiddle::~LynKnockBackMiddle()
{
}

void LynKnockBackMiddle::Initialize()
{
}

void LynKnockBackMiddle::EnterState()
{
	m_info->StartSkill();
	m_info->SetSpeed(0);
	m_info->MoveOn();
	m_bnsMainCam->UnLockTarget();
	m_info->ChangeSkillByState(LYN_SKILL_STATE_CC);


	Vector3 dir = GetVector3(L"knockBackDir");
	m_character->SetVelocity(dir.x * 20, 20, dir.z * 20);
	m_transform->LookAt_RotYAxis(-dir);
	m_animController->Play("Lyn_B_KnockBack_Long_B");
}

void LynKnockBackMiddle::UpdateState()
{
	
	if (m_animController->GetPlayRatio() > 0.1f)
	{
		if (m_character->IsGround())
		{
			m_character->SetVelocityXZ(Vector3(0, 0, 0));
			SetState(L"down");
			return;
		}
	}
	
}

void LynKnockBackMiddle::ExitState()
{
	m_info->EndSkill();
	m_info->MoveOff();

	m_bnsMainCam->LockTarget();
}
