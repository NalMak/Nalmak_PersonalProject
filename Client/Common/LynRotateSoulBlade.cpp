#include "stdafx.h"
#include "LynRotateSoulBlade.h"
#include "BnS_RotateSoulBlade.h"
#include "LynInfo.h"


LynRotateSoulBlade::LynRotateSoulBlade()
{
}


LynRotateSoulBlade::~LynRotateSoulBlade()
{
}

void LynRotateSoulBlade::Initialize()
{
}

void LynRotateSoulBlade::EnterState()
{
	PlayOneShot(L"SoulSword_WrathSoulBlade_Shot");

	m_info->SetResistanceTimer(5.f);

	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 5.f;
		buff.key = L"Z";
		buff.skill = m_skillController->GetSkill(L"rotateSoulBlade");
		auto soulBlade = INSTANTIATE()->AddComponent<BnS_Buff>(&buff)->AddComponent<BnS_RotateSoulBlade>();

		soulBlade->GetComponent<BnS_Buff>()->AddBuffEvent([=](LynInfo* info)
		{
			info->AddInnerPower(3);
			info->ResetBattleTimer();

			AttackInfo::Desc attack;
			attack.colliderType = COLLIDER_TYPE_SPHERE;
			attack.radius = 10.f;
			attack.host = m_gameObject;
			attack.power = (UINT)(m_info->m_power * 0.2f * Nalmak_Math::Rand(0.8f, 1.2f));
			float critical = Nalmak_Math::Rand(0.f, 1.f);
			attack.isCritical = m_info->m_criticalRatio > critical;
			INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
				->AddComponent<AttackInfo>(&attack)
				->SetPosition(m_transform->GetWorldPosition())
				->SetRotation(m_transform->GetWorldRotation());
		}, 1, m_info);
		soulBlade->SetParents(m_gameObject);
	}

	m_info->StartSkill();
	m_info->SetSpeed(0);
			
	if(m_info->GetState() == LYN_STATE_BATTLE_HIDEBLADE)
		m_animController->PlayBlending("Lyn_B_Hide_RotateSoulBlade");
	else
		m_animController->PlayBlending("Lyn_B_Std_RotateSoulBlade");

}

void LynRotateSoulBlade::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.3f)
	{
		m_animController->SetBlendOption(0.3f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}

	if(m_animController->GetPlayRemainTime() < 1.f)
		m_info->EndSkill();
}

void LynRotateSoulBlade::ExitState()
{
	m_info->EndSkill();
}
