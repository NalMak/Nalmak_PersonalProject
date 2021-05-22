#include "stdafx.h"
#include "ZakanPowerATK.h"



ZakanPowerATK::ZakanPowerATK()
{
}


ZakanPowerATK::~ZakanPowerATK()
{
}

void ZakanPowerATK::Initialize()
{
	
}

void ZakanPowerATK::EnterState()
{

	m_info->SetBattleState(BATTLE_STATE_RESISTANCE);

	m_info->LookTarget();
	m_animController->Play("Zakan_B_Spell_Skl_PowerATK_Cast");
}

void ZakanPowerATK::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_PowerATK_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_effect->StartSwordTrail();

			m_jumpTargetPos = m_info->GetTarget()->GetTransform()->GetWorldPosition() + Vector3(0, 10, 0);
			m_landingTargetPos = m_jumpTargetPos + Nalmak_Math::Normalize(m_info->GetTarget()->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition()) * 10.f;

			m_audio->PlayOneShot(L"zakan_powerATK_fire");
			m_animController->Play("Zakan_B_Spell_Skl_PowerATK_Fire");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_PowerATK_Fire")
	{
		Vector3 velocity = m_jumpTargetPos - m_transform->GetWorldPosition();
		if (Nalmak_Math::Length(velocity) > 1)
			m_character->SetVelocity(velocity * 10);
		else
			m_character->SetVelocity(0, 0, 0);
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Skl_PowerATK_Exec1");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Skl_PowerATK_Exec1")
	{
		Vector3 velocity = m_jumpTargetPos - m_transform->GetWorldPosition();
		if (Nalmak_Math::Length(velocity) > 1)
			m_character->SetVelocity(velocity * 5);
		else
			m_character->SetVelocity(0, 0, 0);

		if (m_animController->IsOverTime(0.1f))
		{
			CreateAttack();
		}
		if (m_animController->IsOverTime(0.2f))
		{
			CreateAttack();
		}
		if (m_animController->IsOverTime(0.3f))
		{
			CreateAttack();
		}

		if (!m_animController->IsPlay())
		{
			m_character->SetVelocity(0, 0, 0);
			m_animController->Play("Zakan_B_Skl_PowerATK_Exec2");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Skl_PowerATK_Exec2")
	{

		Vector3 velocity = m_landingTargetPos - m_transform->GetWorldPosition();
		if (Nalmak_Math::Length(velocity) > 1)
			m_character->SetVelocityXZ(velocity * 5);
		

		if (!m_animController->IsPlay())
		{
			m_audio->PlayOneShot(L"zakan_powerATK_end");
			m_animController->Play("Zakan_B_Spell_Skl_PowerATK_End");
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_PowerATK_End")
	{
		if (!m_animController->IsPlay())
		{
			m_character->SetVelocity(0, 0, 0);
			SetState(L"splitBlood");
			return;
		}
	}
}

void ZakanPowerATK::ExitState()
{
	m_effect->EndSwordTrail();

}

void ZakanPowerATK::CreateAttack()
{
	AttackInfo::Desc info;
	info.attackType = ATTACK_TYPE_GROGY;
	info.colliderType = COLLIDER_TYPE_SPHERE;
	info.radius = 10.f;
	info.power = 2000;
	info.host = m_gameObject;
	auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);

	hitBox->SetPosition(m_transform->GetWorldPosition());
}
