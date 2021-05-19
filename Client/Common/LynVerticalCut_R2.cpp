#include "stdafx.h"
#include "LynVerticalCut_R2.h"


LynVerticalCut_R2::LynVerticalCut_R2()
{
}


LynVerticalCut_R2::~LynVerticalCut_R2()
{
}

void LynVerticalCut_R2::Initialize()
{
}

void LynVerticalCut_R2::EnterState()
{


	ReduceInnerPower(2);

	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_02_3");


}

void LynVerticalCut_R2::UpdateState()
{
	if (m_animController->IsOverTime(0.2f))
	{
		/*auto shake = Core::GetInstance()->GetMainCamera()->GetComponent<CameraShake>();
		if (shake)
		{
			shake->Shake(1.f, 2.f, 5, 0.15f, 2, { -1,1,0 });
		}*/
		AttackInfo::Desc attack;
		attack.height = 7;
		attack.depth = 10;
		attack.width = 4;
		CreateAttackInfo(&attack, 6.f, 1.5f, 3.f);
	}

	if (m_animController->IsOverTime(0.15f))
		PlayOneShot(L"SwordMaster_VerticalCut_Wind_Exec");

	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE && !m_isUpper)
	{
		SetState(L"move");
		return;
	}

	if (m_animController->GetPlayRemainTime() < 0.5f)
	{
		m_animController->SetBlendOption(0.35f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (m_info->GetInnerPower() >= 2)
			{
				SetState(L"verticalCut_l2");
				return;
			}
			else
			{
				if (!m_camAudio->IsPlay())
				{
					m_camAudio->SetAudioClip(L"sys_notenoughInnerForce");
					m_camAudio->Play();
				}
			}
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynVerticalCut_R2::ExitState()
{
	m_info->EndSkill();

}
