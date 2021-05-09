#include "stdafx.h"
#include "LynSideDashQ.h"


LynSideDashQ::LynSideDashQ()
{
}


LynSideDashQ::~LynSideDashQ()
{
}

void LynSideDashQ::Initialize()
{
}

void LynSideDashQ::EnterState()
{
	m_bnsMainCam->UnLockTarget();
	m_bnsMainCam->TurnCamera(true, 0.1f);
	m_info->SetSpeed(0.f);

	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_SideMov_E");
	m_animController->SetRootMotion(true);

	Quaternion yRot;
	D3DXQuaternionRotationAxis(&yRot, &Vector3(0, 1, 0), 90 * Rad2Deg);
	m_transform->rotation = m_transform->GetWorldRotation() * yRot;

	Vector3 targetPos = m_info->GetTarget()->GetTransform()->GetWorldPosition();
	Vector3 targetDir = Nalmak_Math::Normalize(targetPos - m_transform->GetWorldPosition());
	Vector3 curPos = m_transform->GetWorldPosition();
	m_targetPos2 = targetPos + targetDir * 4;

	Vector3 centerPos = (curPos + m_targetPos2) * 0.5f;

	m_targetPos1 = centerPos + m_transform->GetRight() * 3.f;
	m_character->SetVelocity((m_targetPos1 - curPos) * 10.f); // 0.25ÃÊ ÀÌµ¿
	m_info->MoveOn();
}

void LynSideDashQ::UpdateState()
{
	if (m_animController->IsOverRealTime(0.1))
	{
		Vector3 target = m_targetPos2;
		Vector3 curPos = m_transform->GetWorldPosition();
		m_character->SetVelocity((target - curPos) * 10.f);
	}
	if (m_animController->IsOverRealTime(0.2))
	{
		m_character->SetVelocity(0, 0, 0);
	}

	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		SetState(L"idle");
		return;
	}
}

void LynSideDashQ::ExitState()
{
	if (m_info->GetState() == LYN_STATE_PEACE_STANDARD)
	{
		m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	}

	m_bnsMainCam->LockTarget();
	m_info->MoveOff();
	m_info->EndSkill();
	m_animController->SetRootMotion(false);

	SetInteger(L"IsBlend", 0);
}
