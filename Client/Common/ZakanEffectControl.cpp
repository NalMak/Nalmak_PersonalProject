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


	ParticleRenderer::Desc particle;
	particle.particleDataName = L"fx_zakanDust";
	particle.PlayOnAwake = false;
	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);

	m_dustParticle = obj->GetComponent<ParticleRenderer>();

	particle.particleDataName = L"fx_zakan_natk";
	particle.PlayOnAwake = false;
	auto obj2 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);

	particle.particleDataName = L"fx_zakan_slash";
	particle.PlayOnAwake = false;
	auto obj3 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<MeshRenderer>()->SetScale(10.f,10.f,10.f);


	m_dustParticle = obj->GetComponent<ParticleRenderer>();
	m_natkParticle = obj2->GetComponent<ParticleRenderer>();
	//m_splitParticle = obj3->GetComponent<ParticleRenderer>();
	//m_splitParticle->GetTransform()->SetParents(m_transform, "WeaponL");
	//m_splitParticle->SetPosition(0,0,0);

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

void ZakanEffectControl::PlayDust()
{
	m_dustParticle->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 12.f);
	m_dustParticle->Play();
}

void ZakanEffectControl::PlayNATK()
{
	m_natkParticle->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * 12.f);
	m_natkParticle->Play();
}

