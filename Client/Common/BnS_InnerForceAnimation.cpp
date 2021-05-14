#include "stdafx.h"
#include "BnS_InnerForceAnimation.h"



BnS_InnerForceAnimation::BnS_InnerForceAnimation(Desc * _desc)
	:SingleImage(&SingleImage::Desc(Vector4(1,1,1,1),_desc->texName))
{
}

BnS_InnerForceAnimation::~BnS_InnerForceAnimation()
{
}

void BnS_InnerForceAnimation::Initialize()
{
	UIComponent::Initialize();

	m_currentRatio = 1.f;
	m_targetRatio = 1.f;
	m_material = GetComponent<CanvasRenderer>()->GetMaterial();
}

void BnS_InnerForceAnimation::Update()
{
	m_currentRatio = Nalmak_Math::Lerp(m_currentRatio, m_targetRatio, dTime * 2.5f);
}

void BnS_InnerForceAnimation::PreRender()
{
}

void BnS_InnerForceAnimation::SetTargetRatio(float _ratio)
{
	m_targetRatio = _ratio;
}

void BnS_InnerForceAnimation::SetCurrentRatio(float _ratio)
{
	m_currentRatio = _ratio;
}

void BnS_InnerForceAnimation::Release()
{
	UIComponent::Release();
}

void BnS_InnerForceAnimation::Render(Shader * _shader, Mesh * _mesh)
{
	_shader->SetFloat("g_changeRatio", m_currentRatio);

	float glow = m_currentRatio * 2;
	if (glow > 1)
	{
		glow = 2 - glow;
	}
	_shader->SetFloat("g_glowRatio", glow * 1.5f);

	
	SingleImage::Render(_shader, _mesh);
}
