#include "stdafx.h"
#include "LynStateThunderbolt.h"


LynStateThunderbolt::LynStateThunderbolt()
{
}


LynStateThunderbolt::~LynStateThunderbolt()
{
}

void LynStateThunderbolt::Initialize()
{
}

void LynStateThunderbolt::EnterState()
{
	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 8.f;
		buff.key = L"F";
		buff.skill = m_skillController->GetSkill(L"thunderbolt");
		INSTANTIATE()->AddComponent<BnS_Buff>(&buff);
	}

	m_info->MoveOn();
	m_info->StartSkill();
	m_bnsMainCam->UnLockTarget();
	m_animController->Play("Lyn_B_CripplingCut_Exec");

	
	Vector3 dir = m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition();
	m_startPos = m_transform->GetWorldPosition();
	dir.y = 0;
	m_direction = Nalmak_Math::Normalize(dir);
	m_targetDistance = Nalmak_Math::Distance(m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_direction, m_transform->GetWorldPosition() );

	m_transform->LookAt_RotYAxis(m_direction);


}

void LynStateThunderbolt::UpdateState()
{

	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_CripplingCut_Exec")
	{
		if (Nalmak_Math::Distance(m_startPos, m_transform->GetWorldPosition()) < m_targetDistance)
		{
			m_character->SetVelocityXZ(m_direction * 20.f);
		}
		else
		{
			m_character->SetVelocityXZ(Vector3(0, 0, 0));
		}
		if (m_animController->IsOverTime(0.7f))
		{
			AttackInfo::Desc attack;
			attack.attackType = ATTACK_TYPE_DOWN;
			attack.ccTime = 3.f;
			attack.depth = 8.f;
			attack.height = 8.f;
			attack.width = 8.f;
			attack.isCritical = true;
			CreateAttackInfo(&attack, 0, 0.f, 20.f);

			m_character->SetVelocityXZ(Vector3(0, 0, 0));
		}

		if (!m_animController->IsPlay())
		{
			
			m_animController->Play("Lyn_B_CripplingCut_Fire");
		}
	}
	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_CripplingCut_Fire")
	{
		m_character->SetVelocityXZ(Vector3(0, 0, 0));

		if (m_animController->GetPlayRemainTime() < 0.2f)
		{
			m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
			SetState(L"idle");
			return;
		}
	}
}

void LynStateThunderbolt::ExitState()
{
	m_info->ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
	m_character->SetVelocityXZ(Vector3(0, 0, 0));
	m_info->MoveOff();
	m_info->EndSkill();
	m_bnsMainCam->LockTarget();
}
