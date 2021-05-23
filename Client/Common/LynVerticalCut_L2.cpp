#include "stdafx.h"
#include "LynVerticalCut_L2.h"
#include "LynAttachedEffect.h"
#include "EffectMove.h"


LynVerticalCut_L2::LynVerticalCut_L2()
{
}


LynVerticalCut_L2::~LynVerticalCut_L2()
{
}

void LynVerticalCut_L2::Initialize()
{

}

void LynVerticalCut_L2::EnterState()
{

	ReduceInnerPower(1);

	m_info->StartSkill();
	m_info->SetState(LYN_STATE_BATTLE_STANDARD);

	m_animController->Play("Lyb_B_Std_VerticalCul_01_3");

	if (m_isUpper)
	{
		// Effect
		MeshRenderer::Desc meshRenderer;
		meshRenderer.meshName = L"SwordTrail_Expand";
		meshRenderer.mtrlName = L"Lyn_VerticalCut";
		LynAttachedEffect::Desc effectDesc;
		effectDesc.emissionPower = 2.f;
		effectDesc.lifeTime = 0.3f;
		effectDesc.emissionBezier = Bezier({ 0.f, 1.f }, { 0.5f, 0.0588235f }, { 1.f, 1.f }, { 1.f, 0.f });

		EffectMove::Desc effectMove;
		effectMove.speed = 50.f;
		effectMove.direction = m_transform->GetForward();
		Quaternion rot;
		D3DXQuaternionRotationYawPitchRoll(&rot, 90.f * Deg2Rad, -30.f* Deg2Rad, 0.f);
		auto effect = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer)->AddComponent<LynAttachedEffect>(&effectDesc)
			->AddComponent<EffectMove>(&effectMove)
			->SetScale(0.1f, 0.1f, 0.1f)->SetRotation(rot * m_transform->GetWorldRotation())
			->SetPosition(m_transform->position.x, m_transform->position.y + 2.f, m_transform->position.z);

		CreateVerticalSlashEffect(false);

	}
}

void LynVerticalCut_L2::UpdateState()
{
	if (m_animController->IsOverTime(0.2f))
	{

		/*auto shake = Core::GetInstance()->GetMainCamera()->GetComponent<CameraShake>();
		if (shake)
		{
			shake->Shake(1.f, 2.f, 5, 0.15f, 2, { 1,1,0 });
		}*/
		AttackInfo::Desc attack;
		attack.height = 7;
		attack.depth = 10;
		attack.width = 4;
		CreateAttackInfo(&attack, 6.f, 1.5f, 3.f);
	}
	if(m_animController->IsOverTime(0.05f))
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
			if (m_info->GetInnerPower() >= 1)
			{
				SetState(L"verticalCut_r2");
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

void LynVerticalCut_L2::ExitState()
{


	m_info->EndSkill();


}
