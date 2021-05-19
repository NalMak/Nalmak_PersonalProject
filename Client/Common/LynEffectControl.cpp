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
	trail.mtrlName = L"Lyn_weapon_trail";
	auto lhand = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_leftHandTrail = lhand->GetComponent<TrailRenderer>();
	auto rhand = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_rightHandTrail = rhand->GetComponent<TrailRenderer>();

	m_leftHandPos = INSTANTIATE();
	m_rightHandPos = INSTANTIATE();
	m_leftHandPos->SetParents(m_gameObject, "WeaponL");
	m_rightHandPos->SetParents(m_gameObject, "WeaponR");



	m_bodyTrail = false;
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
