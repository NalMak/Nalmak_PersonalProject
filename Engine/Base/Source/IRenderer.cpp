#include "..\Include\IRenderer.h"
#include "DeviceManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Animator.h"

USING(Nalmak)

IRenderer::IRenderer()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
	m_renderManager = RenderManager::GetInstance();
}


void IRenderer::Initialize()
{
	m_animator = GetComponent<Animator>();
}

void IRenderer::PreRender()
{
	RenderRequest();
}

void IRenderer::RenderForShadow()
{
}


void IRenderer::RenderRequest()
{
	RenderManager::GetInstance()->RenderRequest(this);
}

float IRenderer::GetBoundingRadius()
{
	return 0.0f;
}

Vector3 IRenderer::GetBoundingCenter()
{
	return { 0,0,0 };
}

void IRenderer::UpdateEachAnimation()
{
	if (m_animator)
		m_animator->UpdateEachAnimation();
}

Animator * IRenderer::GetAnimator()
{
	return m_animator;
}


