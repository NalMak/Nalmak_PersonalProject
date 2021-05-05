#include "stdafx.h"
#include "LynSideDashE.h"


LynSideDashE::LynSideDashE()
{
}


LynSideDashE::~LynSideDashE()
{
}

void LynSideDashE::Initialize()
{
	auto clip = m_animController->GetAnimationClip("Lyn_B_Std_SideMov_E");
	m_turnTotalTime = (float)clip->animationSet->GetPeriod() / clip->speed;




}

void LynSideDashE::EnterState()
{
	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_SideMov_E");
	m_animController->SetRootMotion(true);

	m_turnCurrentTime = 0.f;

	m_startRot = m_transform->GetWorldRotation();
	Quaternion yRot;
	D3DXQuaternionRotationAxis(&yRot, &Vector3(0, 1, 0), 180 * Rad2Deg);
	m_transform->rotation = m_startRot * yRot;
}

void LynSideDashE::UpdateState()
{
	m_turnCurrentTime += dTime;

	//m_transform->RotateY(m_turnCurrentTime / m_turnTotalTime * 180);

	if (!m_animController->IsPlay())
	{
		SetState(L"idle");
		return;
	}
}

void LynSideDashE::ExitState()
{
	m_info->EndSkill();
	m_animController->SetRootMotion(false);
}
