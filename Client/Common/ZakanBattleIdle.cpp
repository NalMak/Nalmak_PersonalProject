#include "stdafx.h"
#include "ZakanBattleIdle.h"


ZakanBattleIdle::ZakanBattleIdle()
{
}


ZakanBattleIdle::~ZakanBattleIdle()
{
}

void ZakanBattleIdle::Initialize()
{
	m_phaseIndex = ZAKAN_PATTERN_DEFAULT1;
	SetInteger(L"phaseChange", 0);


	
	//m_navCollider->SetActive(false);
}

void ZakanBattleIdle::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);

	NavCollider::Desc navCollider;
	navCollider.navName = L"stage1_battleStart";
	m_navCollider = INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_NAVIMESH)->AddComponent<NavCollider>(&navCollider);


	m_phaseIndex = (ZAKAN_PATTERN)GetInteger(L"phaseChange");

	m_character->SetVelocityX(0);
	m_character->SetVelocityZ(0);

	float hpRatio = m_info->GetHpRatio();

	switch (m_phaseIndex)
	{
	case ZAKAN_PATTERN_DEFAULT1:
		if (hpRatio < 0.85f)
			m_phaseIndex = ZAKAN_PATTERN_SPECIAL1;
		break;
	case ZAKAN_PATTERN_DEFAULT2:
		m_phaseIndex = ZAKAN_PATTERN_DEFAULT2;
		if (hpRatio < 0.45f)
			m_phaseIndex = ZAKAN_PATTERN_SPECIAL2;
		break;
	case ZAKAN_PATTERN_DEFAULT3:
		break;
	default:
		break;
	}

	SetInteger(L"phaseChange", m_phaseIndex);
	if (m_phaseIndex == ZAKAN_PATTERN_SPECIAL1 || m_phaseIndex == ZAKAN_PATTERN_SPECIAL2)
	{
		SetState(L"pattern");
		return;
	}
	

	if (m_info->GetDistanceToTarget() < 4.f)
	{
		SetState(L"pattern");
		return;
	}
	else if (BETWEEN(m_info->GetDistanceToTarget(),4,7))
	{
		SetState(L"move");
		return;
	}
	else if (BETWEEN(m_info->GetDistanceToTarget(), 7, 10))
	{
		SetState(L"area360");
		return;
	}
	else if (BETWEEN(m_info->GetDistanceToTarget(), 10, 50))
	{
		SetInteger(L"IsPattern", 0);
		SetState(Nalmak_Math::Random<wstring>(L"powerATK", L"teleport"));

		return;
	}
	//m_animController->PlayBlending("Zakan_B_None_Mov_Idle");
	

}

void ZakanBattleIdle::UpdateState()
{
	
	
}

void ZakanBattleIdle::ExitState()
{
}
