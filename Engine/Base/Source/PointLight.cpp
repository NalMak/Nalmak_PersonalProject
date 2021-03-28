#include "PointLight.h"
#include "Transform.h"


PointLight::PointLight(Desc * _desc)
{
	m_lightInfo.base.color = _desc->color;
	m_lightInfo.base.ambientIntensity = _desc->ambientIntensity;
	m_lightInfo.base.diffuseIntensity = _desc->diffuseIntensity;

	m_lightInfo.radius = _desc->radius;

	m_lightMode = LIGHT_MODE_POINT;
}

PointLight::~PointLight()
{
}

void PointLight::Initialize()
{
	m_lightManager->AddPointLight(this);
}

void PointLight::Update()
{
}

void PointLight::PreRender()
{
	
}


float PointLight::GetRadius()
{
	return m_lightInfo.radius;
}

void PointLight::SetRadius(float _radius)
{
	m_lightInfo.radius = _radius;
}


void PointLight::Release()
{
	m_lightManager->DeletePointLight(this);
}


