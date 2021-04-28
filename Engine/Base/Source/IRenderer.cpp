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

void IRenderer::OnRender(ConstantBuffer & _cBuffer, UINT _containerIndex, UINT _subsetIndex)
{
	m_gameObject->EachRender();
	Render(_cBuffer, _containerIndex,_subsetIndex);
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

void IRenderer::ResetFrustumCulling()
{
	if (m_frustumculling == FRUSTUM_CULLING_STATE_FAIL)
		m_frustumculling = FRUSTUM_CULLING_STATE_READY;
	else if (m_frustumculling == FRUSTUM_CULLING_STATE_SUCCESS)
		m_frustumculling = FRUSTUM_CULLING_STATE_READY;

}


