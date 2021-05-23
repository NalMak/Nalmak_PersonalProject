#include "stdafx.h"
#include "BnS_AfterImageEffect.h"



BnS_AfterImageEffect::BnS_AfterImageEffect(Desc * _desc)
{
	m_originObj = _desc->object;
	m_lifeTime = _desc->lifeTime;
	m_color = _desc->color;

	assert(L"Please Set Object!" && m_originObj);
}

BnS_AfterImageEffect::~BnS_AfterImageEffect()
{
}

void BnS_AfterImageEffect::Initialize()
{
	m_effectMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"BnS_AfterImage_Effect");

	auto skin = m_originObj->GetComponent<SkinnedMeshRenderer>();
	Mesh* mesh = skin->GetMesh();

	SkinnedMeshRenderer::Desc skinDesc;
	skinDesc.meshName = mesh->GetName();
	skinDesc.mtrl = m_effectMaterial;
	AddComponent<SkinnedMeshRenderer>(&skinDesc);

	AnimationController::Desc animDesc;
	animDesc.meshName = mesh->GetName();
	Matrix rotMat;
	animDesc.rootMatrix = *D3DXMatrixRotationY(&rotMat, -90 * Deg2Rad);
	AddComponent<AnimationController>(&animDesc);

	m_transform->scale = m_originObj->GetTransform()->scale;
	m_transform->position = m_originObj->GetTransform()->GetWorldPosition();
	m_transform->rotation = m_originObj->GetTransform()->GetWorldRotation();

	AnimationController* originAnim = m_originObj->GetComponent<AnimationController>();
	auto currentAnimName = originAnim->GetCurrentPlayAnimationName();
	auto newAnimCtrl = GetComponent<AnimationController>();
	auto clip = originAnim->GetCurrentAnimationClip();
	//newAnimCtrl->AddAnimationClip(clip->animationName,0.1f,true);
	//newAnimCtrl->Play(clip->animationName);

}

void BnS_AfterImageEffect::Update()
{
	m_lifeTime -= dTime;

	if (m_lifeTime < 0)
		DESTROY(m_gameObject);
}

void BnS_AfterImageEffect::EachRender()
{
	m_effectMaterial->SetFloat("g_emissionPower", Nalmak_Math::Clamp(m_lifeTime, 0.f, 1.f));
	m_effectMaterial->SetVector("g_color",m_color);

}
