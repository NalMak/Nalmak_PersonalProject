#include "stdafx.h"
#include "BnS_RotateSoulBlade.h"



BnS_RotateSoulBlade::BnS_RotateSoulBlade(Desc * _desc)
{
}

BnS_RotateSoulBlade::~BnS_RotateSoulBlade()
{
}

void BnS_RotateSoulBlade::Initialize()
{
	SkinnedMeshRenderer::Desc skin;
	skin.meshName = L"Lyn_SkinWeapon";
	skin.mtrlName = L"Lyn_SkinWeapon";
	AnimationController::Desc anim;
	anim.meshName = L"Lyn_SkinWeapon";
	TrailRenderer::Desc trail;
	trail.detailCount = 5;
	trail.mtrlName = L"Lyn_weapon_trail";

	m_trailFollowObj[0] = INSTANTIATE();
	m_trailFollowObj[1] = INSTANTIATE();

	auto blade0 = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<TrailRenderer>(&trail)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);
	auto blade1 = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<TrailRenderer>(&trail)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);

	m_soulBlade[0] = blade0->GetComponent<TrailRenderer>();
	m_soulBlade[1] = blade1->GetComponent<TrailRenderer>();


	auto animController0 = m_soulBlade[0]->GetComponent<AnimationController>();
	auto animController1 = m_soulBlade[1]->GetComponent<AnimationController>();
	
	animController0->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_1", 1.5f, true);
	animController1->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_2", 1.5f, true);

	animController0->Play("Lyn_Weapon_RotateSoulBlade_1");
	animController1->Play("Lyn_Weapon_RotateSoulBlade_2");

	m_soulBlade[0]->GetTransform()->SetParents(m_gameObject);
	m_soulBlade[1]->GetTransform()->SetParents(m_gameObject);

	m_trailFollowObj[0]->SetParents(blade0, "_010223_Autoscale");
	m_trailFollowObj[1]->SetParents(blade1, "_010223_Autoscale");


}	

void BnS_RotateSoulBlade::Update()
{
	auto worldPos0 = m_trailFollowObj[0]->GetTransform()->GetWorldPosition();
	auto worldPos1 = m_trailFollowObj[1]->GetTransform()->GetWorldPosition();
	DEBUG_LOG(L"pos", worldPos1);
	m_soulBlade[0]->RecordTrail(worldPos0, worldPos0 + Vector3(0,1,0));
	m_soulBlade[1]->RecordTrail(worldPos1, worldPos1 + Vector3(0,1,0));
}

void BnS_RotateSoulBlade::Release()
{
	DESTROY(m_soulBlade[0]->GetGameObject());
	DESTROY(m_soulBlade[1]->GetGameObject());
}
