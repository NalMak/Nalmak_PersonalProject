#include "stdafx.h"
#include "LynEffectControl.h"
#include "LynInfo.h"
#include "LynWeapon.h"


LynEffectControl::LynEffectControl(Desc * _desc)
{
}

LynEffectControl::~LynEffectControl()
{
}

void LynEffectControl::Initialize()
{
	m_info = GetComponent<LynInfo>();

	m_weaponTrail = m_info->GetWeapon()->GetComponent<LynWeapon>();

	TrailRenderer::Desc trail;
	trail.maxTrailCount = 50;
	trail.detailCount = 7;
	trail.mtrlName = L"Lyn_bodyTrail";
	auto lhand = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_leftHandTrail = lhand->GetComponent<TrailRenderer>();
	auto rhand = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_rightHandTrail = rhand->GetComponent<TrailRenderer>();

	m_leftHandPos = INSTANTIATE();
	m_rightHandPos = INSTANTIATE();
	m_leftHandPos->SetParents(m_gameObject, "WeaponL");
	m_rightHandPos->SetParents(m_gameObject, "WeaponR");



	m_bodyTrail = false;
	ParticleRenderer::Desc particle;
	particle.particleDataName = L"fx_baldo";
	auto baldo = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);
	particle.particleDataName = L"fx_lightningCombo";
	auto lightningCombo = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);

	m_baldoParticle = baldo->GetComponent<ParticleRenderer>();
	m_lightningComboParticle = lightningCombo->GetComponent<ParticleRenderer>();

}

void LynEffectControl::Update()
{
	if (m_bodyTrail)
	{
		Vector3 lHandPos = m_leftHandPos->GetTransform()->GetWorldPosition();
		Vector3 rHandPos = m_rightHandPos->GetTransform()->GetWorldPosition();
	
		m_leftHandTrail->RecordTrail(lHandPos - m_transform->GetRight(), lHandPos - m_transform->GetRight() * 1.2f +  Vector3(0, 0.2f, 0));
		m_rightHandTrail->RecordTrail(rHandPos + m_transform->GetRight(), rHandPos + m_transform->GetRight() * 1.2f + Vector3(0, 0.2f, 0));
	}
	
}

void LynEffectControl::StartWeaponTrail()
{
	m_weaponTrail->StartTrail();
}

void LynEffectControl::EndWeaponTrail()
{
	m_weaponTrail->EndTrail();
}

void LynEffectControl::StartBodyTrail()
{
	m_leftHandTrail->ResetTrail();
	m_leftHandTrail->Play();
	m_rightHandTrail->ResetTrail();
	m_rightHandTrail->Play();
	m_bodyTrail = true;
}

void LynEffectControl::EndBodyTrail()
{
	m_leftHandTrail->ResetTrail();
	m_leftHandTrail->Stop();
	m_rightHandTrail->ResetTrail();
	m_rightHandTrail->Stop();
	m_bodyTrail = false;

}

void LynEffectControl::PlayBaldoEffect()
{
	auto target = m_info->GetTarget();
	if (target)
	{
		m_baldoParticle->SetPosition(target->GetTransform()->GetWorldPosition() - Vector3(0, 3.f, 0) - m_transform->GetRight() * 6);
		Quaternion rot;
		D3DXQuaternionRotationAxis(&rot, &m_transform->GetForward(), -55 * Deg2Rad);
		m_baldoParticle->GetTransform()->rotation = rot;

		m_baldoParticle->Play();
	}
}

void LynEffectControl::PlayLightningComboEffect()
{
	auto target = m_info->GetTarget();
	if (target)
	{
		m_lightningComboParticle->SetPosition(target->GetTransform()->GetWorldPosition() - Vector3(0,5.f,0) + m_transform->GetRight() * 6);
		Quaternion rot;
		D3DXQuaternionRotationAxis(&rot, &m_transform->GetForward(), 45 * Deg2Rad);
		m_lightningComboParticle->GetTransform()->rotation = rot;
		m_lightningComboParticle->Play();
	}
}
