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
	m_info->SetResistance(true);
	m_effect->StartBodyTrail();

	PlayOneShot(L"Fencer_BackStep_Shot");

	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 6.f;
		buff.key = L"Q";
		buff.skill = m_skillController->GetSkill(L"sideDashQ");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);
	}

	AddInnerPower(1);
	m_bnsMainCam->UnLockTarget();

	m_info->SetSpeed(0.f);

	m_info->StartSkill();
	m_animController->Play("Lyn_B_Std_SideMov_E");
	//m_animController->SetRootMotion(true);

	Quaternion yRot;
	D3DXQuaternionRotationAxis(&yRot, &Vector3(0, 1, 0), 90 * Rad2Deg);
	m_transform->rotation = m_transform->GetWorldRotation() * yRot;

	Vector3 targetPos = m_info->GetTarget()->GetTransform()->GetWorldPosition();
	targetPos.y = m_transform->position.y;

	Vector3 targetDir = Nalmak_Math::Normalize(targetPos - m_transform->GetWorldPosition());
	Vector3 curPos = m_transform->GetWorldPosition();
	m_targetPos2 = targetPos + targetDir * 6;

	Vector3 centerPos = (curPos + m_targetPos2) * 0.5f;

	m_targetPos1 = centerPos - m_transform->GetRight() * 3.f;
	m_character->SetVelocity((m_targetPos1 - curPos) * 1 / ((float)BNS_SIDE_DASH_TIME * 0.5f)); // 0.25?? ?̵?

	m_info->MoveOn();
	float angle = acosf(Nalmak_Math::Dot(m_transform->GetForward(), targetDir));
	Vector3 cross = Nalmak_Math::Cross(m_transform->GetForward(), targetDir);

	m_bnsMainCam->TurnCamera(angle * Nalmak_Math::Sign(cross.z), false, 0.1f);
}

void LynSideDashQ::UpdateState()
{
	if (m_animController->IsOverRealTime(BNS_SIDE_DASH_TIME * 0.5))
	{
		Vector3 target = m_targetPos2;
		Vector3 curPos = m_transform->GetWorldPosition();
		m_character->SetVelocity((target - curPos) * 1 / (float)(BNS_SIDE_DASH_TIME * 0.5f));
	}
	if (m_animController->IsOverRealTime(BNS_SIDE_DASH_TIME))
	{
		m_character->SetVelocity(0, 0, 0);
	}

	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (m_info->GetState() != LYN_STATE_BATTLE_HIDEBLADE)
			{
				if (m_info->GetInnerPower() >= 2)
				{
					SetState(L"verticalCut_l2");
					return;
				}
			}
		}
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);

		SetState(L"idle");
		return;
	}
}

void LynSideDashQ::ExitState()
{
	if (m_info->GetState() != LYN_STATE_BATTLE_HIDEBLADE)
	{
		m_info->SetState(LYN_STATE_BATTLE_STANDARD);
		m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);

	}

	m_effect->EndBodyTrail();

	m_info->SetResistance(false);
	m_info->SetResistanceTimer(0.5f);


	m_bnsMainCam->LockTarget();
	m_info->MoveOff();
	m_info->EndSkill();
	//m_animController->SetRootMotion(false);

}
