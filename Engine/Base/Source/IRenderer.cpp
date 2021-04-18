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
}

void IRenderer::PreRender()
{
	RenderRequest();
}

void IRenderer::OnRender(ConstantBuffer & _cBuffer)
{
	m_gameObject->EachRender();
	Render(_cBuffer);
}


void IRenderer::RenderForShadow(Shader * _shader)
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


