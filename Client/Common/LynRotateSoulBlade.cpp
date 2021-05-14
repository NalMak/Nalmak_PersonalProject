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
	if (m_isUpper)
	{
		BnS_Buff::Desc buff;
		buff.buffTimer = 5.f;
		buff.key = L"Z";
		buff.skill = m_skillController->GetSkill(L"rotateSoulBlade");
		auto soulBlade = INSTANTIATE()->AddComponent<BnS_Buff>(&buff)->AddComponent<BnS_RotateSoulBlade>();

		soulBlade->GetComponent<BnS_Buff>()->AddBuffEvent([](LynInfo* info)
		{
			info->AddInnerPower(3);
			info->ResetBattleTimer();
		}, 1, m_info);
		soulBlade->SetParents(m_gameObject);
	}

	m_info->StartSkill();
	m_info->SetSpeed(0);
			
	if(m_info->GetState() == LYN_STATE_BATTLE_HIDEBLADE)
		m_animController->Play("Lyn_B_Hide_RotateSoulBlade");
	else
		m_animController->Play("Lyn_B_Std_RotateSoulBlade");

}

void LynRotateSoulBlade::UpdateState()
{
	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		m_animController->SetBlendOption(0.5f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		SetState(L"idle");
		return;
	}
}

void LynRotateSoulBlade::ExitState()
{
	m_info->EndSkill();
}
