#include "..\Include\IRenderer.h"
#include "DeviceManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Transform.h"

USING(Nalmak)

IRenderer::IRenderer()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
}


void IRenderer::PreRender()
{
	RenderRequest();
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


