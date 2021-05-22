#include "stdafx.h"
#include "ZakanSmash.h"
#include "LynInfo.h"


ZakanSmash::ZakanSmash()
{
}


ZakanSmash::~ZakanSmash()
{
}

void ZakanSmash::Initialize()
{
}

void ZakanSmash::EnterState()
{
	m_effect->StartSwordTrail();
	m_info->SetBattleState(BATTLE_STATE_WEAK);

	m_info->LookTarget();
	m_animController->Play("Zakan_B_Spell_Skl_Smash_Cast");
}

void ZakanSmash::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_audio->PlayOneShot(L"zakan_smash1");

			m_animController->Play("Zakan_B_Spell_Skl_Smash_Exec1");

			GameObject* lyn = m_info->GetTarget();
			Vector3 dir = lyn->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition();
			dir.y = 0;
			float distance = Nalmak_Math::Length(dir);
			dir = Nalmak_Math::Normalize(dir);
			if (Nalmak_Math::Dot(dir, m_transform->GetForward()) > 0)
			{
				if (distance < 5 / BNS_DISTANCE_RATIO)
				{
					AttackInfo::Desc attackInfo;
					attackInfo.host = m_gameObject;
					attackInfo.power = 1500;
					AttackInfo attack(&attackInfo);
					lyn->GetComponent<LynInfo>()->HitByAttackInfo(&attack);
				}
			}

			return;
		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Exec1")
	{
		if (!m_animController->IsPlay())
		{
			m_audio->PlayOneShot(L"zakan_smash2");

			m_animController->Play("Zakan_B_Spell_Skl_Smash_Exec2");

			GameObject* lyn =  m_info->GetTarget();
			Vector3 dir =lyn->GetTransform()->GetWorldPosition() - m_transform->GetWorldPosition();
			dir.y = 0;
			float distance = Nalmak_Math::Length(dir);
			dir = Nalmak_Math::Normalize(dir);
			if (Nalmak_Math::Dot(dir, m_transform->GetForward()) > 0)
			{
				if (distance < 5 / BNS_DISTANCE_RATIO)
				{
					AttackInfo::Desc attackInfo;
					attackInfo.host = m_gameObject;
					attackInfo.power = 1500;
					attackInfo.attackType = ATTACK_TYPE_GROGY;
					attackInfo.ccTime = 2.f;
					AttackInfo attack(&attackInfo);
					lyn->GetComponent<LynInfo>()->HitByAttackInfo(&attack);
				}
			}
			return;
		}

	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Skl_Smash_Exec2")
	{
		if (m_animController->IsOverTime(0.4f))
		{
			m_effect->EndSwordTrail();
		}
		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
}

void ZakanSmash::ExitState()
{
	m_effect->EndSwordTrail();

}
