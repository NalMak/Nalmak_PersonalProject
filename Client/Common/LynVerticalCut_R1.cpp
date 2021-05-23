#include "stdafx.h"
#include "LynVerticalCut_R1.h"
#include "LynAttachedEffect.h"
#include "EffectMove.h"


LynVerticalCut_R1::LynVerticalCut_R1()
{
}


LynVerticalCut_R1::~LynVerticalCut_R1()
{
}

void LynVerticalCut_R1::Initialize()
{
}

void LynVerticalCut_R1::EnterState()
{
	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);
	m_animController->Play("Lyb_B_Std_VerticalCul_02_2");
	PlayOneShot(L"SwordMaster_VerticalCut_Cast");

	if (m_isUpper)
	{
		// Effect
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"SwordTrail_Expand";
		meshRenderer.mtrlName = L"Lyn_VerticalCut";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 1.f;
		effectDesc.lifeTime = 0.6f;
		//effectDesc.emissionBezier = Bezier({ 0.f, 1.f }, { 0.5f, 0.0588235f }, { 1.f, 1.f }, { 1.f, 0.f });

		EffectMove::Desc effectMove;
		effectMove.speed = 50.f;
		effectMove.direction = m_transform->GetForward();
		Quaternion rot;
		D3DXQuaternionRotationYawPitchRoll(&rot, 90.f * Deg2Rad, 30.f* Deg2Rad, 0.f);
		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->AddComponent<EffectMove>(&effectMove)
			->SetScale(0.1f, 0.1f, 0.1f)->SetRotation(rot * m_transform->GetWorldRotation())
			->SetPosition(m_transform->position.x, m_transform->position.y + 2.f, m_transform->position.z);

	}
}

void LynVerticalCut_R1::UpdateState()
{
	if (m_info->GetDirectionState() != LYN_MOVE_DIR_STATE_NONE && !m_isUpper)
	{
		SetState(L"move");
		return;
	}

	if (m_animController->GetPlayRemainTime() < 0.2f)
	{
		m_animController->SetBlendOption(0.2f, 1.f, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (m_info->GetInnerPower() >= 2)
			{
				SetState(L"verticalCut_l2");
				return;
			}
		}
		else
		{
			SetState(L"idle");
			return;
		}
	}
}

void LynVerticalCut_R1::ExitState()
{
	m_info->EndSkill();


}
