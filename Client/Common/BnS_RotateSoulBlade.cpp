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
	m_soulBlade[0] = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);
	m_soulBlade[1] = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>(&skin)->AddComponent<AnimationController>(&anim)->SetScale(0.1f, 0.1f, 0.1f);

	auto animController0 = m_soulBlade[0]->GetComponent<AnimationController>();
	auto animController1 = m_soulBlade[1]->GetComponent<AnimationController>();
	
	animController0->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_1", 1.5f, true);
	animController1->AddAnimationClip("Lyn_Weapon_RotateSoulBlade_2", 1.5f, true);

	animController0->Play("Lyn_Weapon_RotateSoulBlade_1");
	animController1->Play("Lyn_Weapon_RotateSoulBlade_2");

	m_soulBlade[0]->SetParents(m_gameObject);
	m_soulBlade[1]->SetParents(m_gameObject);

}	

void BnS_RotateSoulBlade::Update()
{
}

void BnS_RotateSoulBlade::Release()
{
	DESTROY(m_soulBlade[0]);
	DESTROY(m_soulBlade[1]);
}
