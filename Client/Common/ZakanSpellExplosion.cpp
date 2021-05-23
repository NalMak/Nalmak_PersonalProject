#include "stdafx.h"
#include "ZakanSpellExplosion.h"
#include "EnemyState.h"
#include "LynInfo.h"
#include "UIManager.h"


ZakanSpellExplosion::ZakanSpellExplosion()
{
}


ZakanSpellExplosion::~ZakanSpellExplosion()
{
}

void ZakanSpellExplosion::Initialize()
{
}

void ZakanSpellExplosion::EnterState()
{
	//m_info->LookTarget();

	UIManager::GetInstance()->NotifySystemUI(L"자칸이 천공파열을 사용합니다");

	m_animController->Play("Zakan_B_Spell_Explosion_Cast");
	m_audio->PlayOneShot(L"Zakan_SpellExplosion_Cast1-1");

}

void ZakanSpellExplosion::UpdateState()
{
	if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Explosion_Cast")
	{
		if (!m_animController->IsPlay())
		{
			m_animController->Play("Zakan_B_Spell_Explosion_Exec");
			m_audio->PlayOneShot(L"Zakan_SpellExplosion_Exec1");

		}
	}
	else if (m_animController->GetCurrentPlayAnimationName() == "Zakan_B_Spell_Explosion_Exec")
	{
		if (m_animController->IsOverTime(4.f))
		{
			AttackInfo::Desc info;
			info.attackType = ATTACK_TYPE_KNOCKBACK_MIDDLE;
			info.power = 4000;
			info.host = m_gameObject;

			AttackInfo  attck(&info);
			m_info->GetTarget()->GetComponent<LynInfo>()->HitByAttackInfo(&attck);
		}
	
		if (!m_animController->IsPlay())
		{
			m_character->SetVelocity(0, 0, 0);
			SetState(L"battle_idle");
			return;
		}
	}
	


}

void ZakanSpellExplosion::ExitState()
{
}
