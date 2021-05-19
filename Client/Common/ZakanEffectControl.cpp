#include "stdafx.h"
#include "ZakanEffectControl.h"


ZakanEffectControl::ZakanEffectControl(Desc* _desc)
{
}


ZakanEffectControl::~ZakanEffectControl()
{
}

void ZakanEffectControl::Initialize()
{
}

void ZakanEffectControl::Update()
{
}

void ZakanEffectControl::PreRender()
{
	m_swordTrail->RecordTrail(m_swordTrailStart->GetTransform()->GetWorldPosition(), m_swordTrailEnd->GetTransform()->GetWorldPosition());
}

void ZakanEffectControl::CreateWeaponTrailEffect(GameObject * _weapon)
{
	m_swordTrailStart = INSTANTIATE()->SetPosition(0,40,0);
	m_swordTrailEnd = INSTANTIATE()->SetPosition(0,300,0);

	m_swordTrail = _weapon->GetComponent<TrailRenderer>();

	m_swordTrailStart->SetParents(_weapon);
	m_swordTrailEnd->SetParents(_weapon);

}

void ZakanEffectControl::StartSwordTrail()
{
	m_swordTrail->ResetTrail();
	m_swordTrail->Play();
}

void ZakanEffectControl::EndSwordTrail()
{
	m_swordTrail->ResetTrail();
	m_swordTrail->Stop();
}
