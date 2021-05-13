#include "stdafx.h"
#include "LynThrowSoulBlade.h"
#include "LynWeapon.h"


LynThrowSoulBlade::LynThrowSoulBlade()
{
}


LynThrowSoulBlade::~LynThrowSoulBlade()
{
}

void LynThrowSoulBlade::Initialize()
{
	m_weapon = m_info->GetWeapon()->GetComponent<LynWeapon>();
}

void LynThrowSoulBlade::EnterState()
{
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);

	m_animController->Play("Lyn_B_Throw1");
	m_target = m_info->GetTarget();
}

void LynThrowSoulBlade::UpdateState()
{
	

	if (m_animController->GetCurrentPlayAnimationName() == "Lyn_B_Throw1")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Lyn_B_Throw2");

			if (m_isUpper)
			{
				m_weapon->GetTransform()->DeleteParent();
				m_weapon->SetPosition(m_info->GetRightHandPosition());
				m_weapon->CreateAttackInfo();
			}
		}
	}
	else
	{
		if (m_isUpper)
		{
			if (m_weapon->GetWeaponState() == LynWeapon::LYN_WEAPON_THROW_STATE_THROW)
			{
				m_weapon->ChaseTarget(m_target->GetTransform()->GetWorldPosition());
			}
			else if (m_weapon->GetWeaponState() == LynWeapon::LYN_WEAPON_THROW_STATE_RETURN)
			{
				m_weapon->ChaseTarget(m_info->GetRightHandPosition());
			}
		}

		if (m_weapon->GetWeaponState() == LynWeapon::LYN_WEAPON_THROW_STATE_NONE)
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynThrowSoulBlade::ExitState()
{
	m_info->EndSkill();
	m_target = nullptr;
}
