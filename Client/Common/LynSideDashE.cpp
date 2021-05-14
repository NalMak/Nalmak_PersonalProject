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
	
}

void LynSideDashE::EnterState()
{
	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 6.f;
		buff.key = L"E";
		buff.skill = m_skillController->GetSkill(L"sideDashE");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);
	}

	m_info->AddInnerPower(1);

	m_info->SetSpeed(0.f);

	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_SideMov_E");
	//m_animController->SetRootMotion(true);


	Quaternion yRot;
	D3DXQuaternionRotationAxis(&yRot, &Vector3(0, 1, 0), 90 * Rad2Deg);
	m_transform->rotation = m_transform->GetWorldRotation() * yRot;

	Vector3 targetPos = m_info->GetTarget()->GetTransform()->GetWorldPosition();
	Vector3 targetDir = Nalmak_Math::Normalize(targetPos - m_transform->GetWorldPosition());

	Vector3 curPos = m_transform->GetWorldPosition();
	m_targetPos2 = targetPos + targetDir * 6;

	Vector3 centerPos = (curPos + m_targetPos2) * 0.5f;

	{
		m_targetPos1 = centerPos + m_transform->GetRight() * 3.f;
		m_character->SetVelocity((m_targetPos1 - curPos) * 10.f ); // 0.25�� �̵�
	}
	m_info->MoveOn();
	m_bnsMainCam->UnLockTarget();

	float angle = acosf(Nalmak_Math::Dot(m_transform->GetForward(), targetDir));
	Vector3 cross = Nalmak_Math::Cross(m_transform->GetForward(), targetDir);

	m_bnsMainCam->TurnCamera(angle * Nalmak_Math::Sign(cross.z), true, 0.1f);
}

void LynSideDashE::UpdateState()
{
	float ratio = m_animController->GetPlayRatio();

	if (m_animController->IsOverRealTime(0.1))
	{
		Vector3 target = m_targetPos2;
		Vector3 curPos = m_transform->GetWorldPosition();
		m_character->SetVelocity((target - curPos) * 10.f);
	}
	if (m_animController->IsOverRealTime(0.2))
	{
		m_character->SetVelocity(0,0,0);
	}

	

	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (m_info->GetInnerPower() >= 2)
			{
				SetState(L"verticalCut_r2");
				return;
			}
		}
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

		SetState(L"idle");
		return;
	}
}

void LynSideDashE::ExitState()
{
	if (m_info->GetState() == LYN_STATE_PEACE_STANDARD)
	{
		m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	}

	m_bnsMainCam->LockTarget();
	m_info->MoveOff();
	m_info->EndSkill();
	//m_animController->SetRootMotion(false);

}
