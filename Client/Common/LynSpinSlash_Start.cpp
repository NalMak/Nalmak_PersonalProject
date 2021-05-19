#include "stdafx.h"
#include "LynSpinSlash_Start.h"


LynSpinSlash_Start::LynSpinSlash_Start()
{
}


LynSpinSlash_Start::~LynSpinSlash_Start()
{
}

void LynSpinSlash_Start::Initialize()
{
	attack.soundName = L"SwordMaster_SpinSlash_Shot";
	attack.colliderType = COLLIDER_TYPE_SPHERE;
	attack.radius = 5.f;
}

void LynSpinSlash_Start::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyn_B_Std_SpinSlash_01");
	m_info->StartSkill();
	PlayOneShot(L"lyn_spinSlash");

	//m_animController->SetAnimatinoOffsetByBeizer({ 0,0,0 }, { 0,-0.5f,0 }, 0.75f, { 0,0 }, { 0.179f,0.01f }, { 0.82f,0.75f }, { 1,0 });
}

void LynSpinSlash_Start::UpdateState()
{
	if (m_animController->IsOverTime(0.3f))
	{
		CreateAttackInfo(&attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(0.45f))
	{
		CreateAttackInfo(&attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(0.85f))
	{
		CreateAttackInfo(&attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(1.05f))
	{
		CreateAttackInfo(&attack, 0.f, 1.f, 0.3f);
	}
	else if (m_animController->IsOverTime(1.2f))
	{
		CreateAttackInfo(&attack, 0.f, 1.f, 0.3f);
	}
	if (!m_animController->IsPlay())
	{
		SetState(L"spinSlash_end");
	}
}

void LynSpinSlash_Start::ExitState()
{
	m_info->EndSkill();
	m_info->SetBattleState(BATTLE_STATE_WEAK);

}
