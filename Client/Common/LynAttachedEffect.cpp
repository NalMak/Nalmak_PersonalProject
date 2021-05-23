#include "stdafx.h"
#include "LynAttachedEffect.h"




LynAttachedEffect::LynAttachedEffect(Desc * _desc)
{
	m_scaleAnimation = _desc->scaleAnimation;

	m_rotateAxis = _desc->rotateAxis;
	m_rotateSpeed = _desc->rotateSpeed;

	m_emissionBezier = _desc->emissionBezier;

	m_totalLifeTime = _desc->lifeTime;
	m_currentLifeTime = 0;

	m_emissionPower = _desc->emissionPower;
	m_currentEmissionPower = m_emissionPower;

	m_yAxisAngle = _desc->yAxisAngle;
}

LynAttachedEffect::~LynAttachedEffect()
{
}

void LynAttachedEffect::Initialize()
{
	m_material = GetComponent<MeshRenderer>()->GetMaterial();


}

void LynAttachedEffect::Update()
{
	m_currentLifeTime += dTime;
	if (m_totalLifeTime < m_currentLifeTime)
	{
		DESTROY(m_gameObject);
	}
	
	if (m_rotateSpeed != 0)
	{
		Quaternion rot;
		D3DXQuaternionRotationAxis(&rot, &m_rotateAxis, m_rotateSpeed * dTime * Deg2Rad);
		m_transform->rotation *= rot;
	}

	m_transform->scale += m_scaleAnimation * dTime;
	m_lifeTimeRatio = m_currentLifeTime / m_totalLifeTime;
	m_currentEmissionPower =  m_emissionBezier.GetYvalue(m_lifeTimeRatio) * m_emissionPower;
}

void LynAttachedEffect::EachRender()
{
	m_material->SetFloat("g_emissionPower", m_currentEmissionPower);
	m_material->SetFloat("g_lifeTimeRatio", m_lifeTimeRatio);
}
