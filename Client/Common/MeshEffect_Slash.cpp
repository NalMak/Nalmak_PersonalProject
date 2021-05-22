#include "stdafx.h"
#include "MeshEffect_Slash.h"


MeshEffect_Slash::MeshEffect_Slash(Desc * _desc)
{
	m_emissionChange = _desc->emissionChange;
	m_scaleChange = _desc->scaleChange;
}

MeshEffect_Slash::~MeshEffect_Slash()
{
}

void MeshEffect_Slash::Initialize()
{
	auto meshRenderer = GetComponent<MeshRenderer>();
	m_mesh = meshRenderer->GetMesh();
	m_material= meshRenderer->GetMaterial();

	m_currentEmissionPower = 0.3f;
}

void MeshEffect_Slash::Update()
{
	m_currentEmissionPower += m_emissionChange * dTime;
	m_transform->scale += m_scaleChange * dTime;
	if (m_currentEmissionPower < 0)
		m_currentEmissionPower = 0;
	if (m_transform->scale.x < 0)
		m_transform->scale.x = 0;
	if (m_transform->scale.y < 0)
		m_transform->scale.y = 0;
	if (m_transform->scale.z < 0)
		m_transform->scale.z = 0;
}

void MeshEffect_Slash::EachRender()
{
	m_material->SetFloat("g_emissionPower", m_currentEmissionPower);

}
