#include "DirectionalLight.h"
#include "LightManager.h"
#include "Transform.h"
#include "DirectionalLight.h"
#include "Camera.h"
DirectionalLight::DirectionalLight(Desc * _desc)
{
	m_info.base.color = _desc->color;
	m_info.base.diffuseIntensity = _desc->diffuseIntensity;
	m_info.base.ambientIntensity = _desc->ambientIntensity;

	m_lightMode = LIGHT_MODE_DIRECTIONAL;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Initialize()
{


	m_lightManager->SetDirectionalLightInfo(this);
	CreateLightCam();
}

void DirectionalLight::Update()
{
	

	
}

void DirectionalLight::PreRender()
{
	m_lightCam->UpdateViewMatrix();
	m_lightCam->UpdateFrustumPlane();

	m_info.direction = m_transform->GetForward();
	m_info.lightViewProj = m_lightCam->GetViewMatrix() * m_lightCam->GetProjMatrix();

	m_transform->position = -m_info.direction * 150;
	m_info.base.position = m_transform->position;

}

void DirectionalLight::Release()
{
	m_lightManager->DeleteDirectionalLight();
}

const DirectionalLightInfo& DirectionalLight::GetDirectionalLightInfo()
{
	return m_info;
}

void DirectionalLight::CreateLightCam()
{
	Camera::Desc camDesc;
	camDesc.fovY = D3DX_PI * 0.3f;
	camDesc.zNear = 1.f;
	camDesc.zFar = 400.f;
	camDesc.aspect = 1;
	AddComponent<Camera>(&camDesc);
	m_lightCam = GetComponent<Camera>();
	m_lightCam->SetActive(false);

	m_transform->position = { 0,100,0 };
	m_info.base.position = m_transform->position;
}

Camera * DirectionalLight::GetLightCamera()
{
	return m_lightCam;
}


