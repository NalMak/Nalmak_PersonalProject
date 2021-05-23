#include "stdafx.h"
#include "BnS_AttackArea_ScaleAnim.h"



BnS_AttackArea_ScaleAnim::BnS_AttackArea_ScaleAnim(Desc * _desc)
{
	m_lifeTime = 0;
	m_totalLifeTime = _desc->lifeTime;;
	m_startScale = _desc->startScale;
	m_targetScale = _desc->targetScale;
}

BnS_AttackArea_ScaleAnim::~BnS_AttackArea_ScaleAnim()
{
}

void BnS_AttackArea_ScaleAnim::Initialize()
{
	MeshRenderer::Desc mesh;
	mesh.mtrl = ResourceManager::GetInstance()->GetResource<Material>(L"zakan_attackAreaRect3");
	mesh.meshName = L"1x1Rect";
	AddComponent<MeshRenderer>(&mesh);
}

void BnS_AttackArea_ScaleAnim::Update()
{
	m_lifeTime += dTime;

	if (m_lifeTime > m_totalLifeTime)
	{
		DESTROY(m_gameObject);
		return;
	}

	m_transform->scale = Nalmak_Math::Lerp(m_startScale, m_targetScale, m_lifeTime / m_totalLifeTime);
}
