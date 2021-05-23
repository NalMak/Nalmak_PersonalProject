#include "stdafx.h"
#include "BnS_AttackArea.h"


BnS_AttackArea::BnS_AttackArea(Desc * _desc)
{
	m_totalTimer = _desc->timer;
	m_timer = 0;
	m_attackAreaMtrl = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);

	
}

BnS_AttackArea::~BnS_AttackArea()
{
}

void BnS_AttackArea::Initialize()
{
	MeshRenderer::Desc mesh;
	mesh.mtrl = m_attackAreaMtrl;
	mesh.meshName = L"1x1Rect";
	AddComponent<MeshRenderer>(&mesh);
}

void BnS_AttackArea::Update()
{
	m_timer += dTime;

	if (m_totalTimer < m_timer)
	{
		DESTROY(m_gameObject);
	}
}

void BnS_AttackArea::EachRender()
{

	m_attackAreaMtrl->SetFloat("g_lifeTimeRatio", m_timer / m_totalTimer);
}
