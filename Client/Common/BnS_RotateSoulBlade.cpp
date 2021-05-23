#include "stdafx.h"
#include "BnS_RotateSoulBlade.h"
#include "LynEffectControl.h"



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
	trail.maxTrailCount = 10;
	trail.mtrlName = L"Lyn_weapon_soulbladeTrail";



	auto blade0 = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<TrailRenderer>(&trail)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);
	auto blade1 = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<TrailRenderer>(&trail)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);
	m_soulBlade[0] = blade0->GetComponent<TrailRenderer>();
	m_soulBlade[1] = blade1->GetComponent<TrailRenderer>();
	m_soulBlade[0]->GetTransform()->SetParents(m_gameObject);
	m_soulBlade[1]->GetTransform()->SetParents(m_gameObject);

	auto animController0 = m_soulBlade[0]->GetComponent<AnimationController>();
	auto animController1 = m_soulBlade[1]->GetComponent<AnimationController>();
	
	animController0->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_1", 1.f, true);
	animController1->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_2", 1.f, true);

	animController0->Play("Lyn_Weapon_RotateSoulBlade_1");
	animController1->Play("Lyn_Weapon_RotateSoulBlade_2");



	auto obj = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	m_trailFollowObj[0] = INSTANTIATE();
	m_trailFollowObj[1] = INSTANTIATE();
	m_trailFollowObj[0]->SetParents(blade0, "WeaponRoot");
	m_trailFollowObj[1]->SetParents(blade1, "_010223_Autoscale");
	m_trailFollowObj[0]->SetPosition(0, 0, 0);
	m_trailFollowObj[1]->SetPosition(0, 0, 0);

	m_boneMatrix[0] = blade1->GetComponent<SkinnedMeshRenderer>()->GetBoneWorldMatrix("WeaponRoot");
	m_boneMatrix[1] = blade1->GetComponent<SkinnedMeshRenderer>()->GetBoneWorldMatrix("_010223_Autoscale");



	// default
// WeaponRoot
	//_010223_Autoscale
}	

void BnS_RotateSoulBlade::Update()
{
	auto worldMat0 = *m_boneMatrix[0] * m_trailFollowObj[0]->GetTransform()->GetWorldMatrix();
	auto worldMat1 = *m_boneMatrix[1] * m_trailFollowObj[1]->GetTransform()->GetWorldMatrix();

	Vector3 worldPos0 = Vector3(worldMat0._41, worldMat0._42, worldMat0._43);
	Vector3 worldPos1 = Vector3(worldMat1._41, worldMat1._42, worldMat1._43);


	DEBUG_LOG(L"pos", worldPos1);
	DEBUG_LOG(L"pos2", worldPos1);


	m_soulBlade[0]->RecordTrail(worldPos0, worldPos0 + Vector3(0,0.3f,0));
	m_soulBlade[1]->RecordTrail(worldPos1, worldPos1 + Vector3(0,0.3f,0));

	//m_soulBlade[1]->RecordTrail(obj->GetTransform()->GetWorldPosition(), obj->GetTransform()->GetWorldPosition() + Vector3(0, 10, 0));

}

void BnS_RotateSoulBlade::Release()
{
	DESTROY(m_soulBlade[0]->GetGameObject());
	DESTROY(m_soulBlade[1]->GetGameObject());
}
