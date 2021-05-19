#include "stdafx.h"
#include "ZakanChange.h"


ZakanChange::ZakanChange()
{
}


ZakanChange::~ZakanChange()
{
}

void ZakanChange::Initialize()
{
	auto skin = GetComponent<SkinnedMeshRenderer>();
	m_armMaterial = skin->GetMaterial(0);
	m_bodyMaterial = skin->GetMaterial(2);

}

void ZakanChange::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);
	m_animController->Play("zakan_summon_cast");
	m_emissioinPower = 0.f;
}

void ZakanChange::UpdateState()
{
	m_armMaterial->SetFloat("g_specularPower", m_emissioinPower);
	m_bodyMaterial->SetFloat("g_specularPower", m_emissioinPower);

	if (!m_animController->IsPlay("zakan_summon_cast"))
	{
		m_animController->Play("zakan_summon_exec");
		
	}
	if (m_animController->GetCurrentPlayAnimationName() == "zakan_summon_exec")
	{
		m_emissioinPower += dTime * 4.5f;


		if (!m_animController->IsPlay())
		{
			SetState(L"battle_idle");
			return;
		}
	}
	

}

void ZakanChange::ExitState()
{
}
