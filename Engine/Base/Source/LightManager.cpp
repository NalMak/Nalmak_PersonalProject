#include "LightManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "Camera.h"

IMPLEMENT_SINGLETON(LightManager)

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::Initialize()
{
	m_isSkyBoxRender = false;
	m_skyBoxMesh = ResourceManager::GetInstance()->GetResource<Mesh>(L"skyBox");
	m_skyBoxMtrl = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_SkyBox");
	m_skyBoxMtrl->SetTexture("g_skyBox", L"skyBox_default");

}

void LightManager::SetSkyBox(const wstring & _skyBoxName)
{
	m_isSkyBoxRender = true;
	m_skyBoxMtrl->SetTexture("g_skyBox", _skyBoxName);
}

void LightManager::ResetSkyBox()
{
	m_isSkyBoxRender = false;
}

void LightManager::SetDirectionalLightInfo(DirectionalLight * _light)
{
	if (m_directionalLight)
		assert(L"Already Directional light is exist!" && 0);

	m_directionalLight = _light;

}

void LightManager::DeleteDirectionalLight()
{
	m_directionalLight = nullptr;
}

void LightManager::DeletePointLight(PointLight * _light)
{
	for (auto iter = m_pointLights.begin(); iter != m_pointLights.end(); ++iter)
	{
		if ((*iter) == _light)
		{
			m_pointLights.erase(iter);
			return;
		}
	}
}

void LightManager::AddPointLight(PointLight * _light)
{
	m_pointLights.emplace_back(_light);
}

const DirectionalLightInfo & LightManager::GetDirectionalLightInfo()
{
	return m_directionalLight->GetDirectionalLightInfo();
}

bool LightManager::IsExistDirectionalLight()
{
	if (m_directionalLight)
		return true;
	else
		return false;
}


Camera * LightManager::GetLightCamera()
{
	return m_directionalLight->GetLightCamera();
}

Mesh * LightManager::GetSkyboxMesh()
{
	return m_skyBoxMesh;
}

Material * LightManager::GetSkyboxMaterial()
{
	return m_skyBoxMtrl;
}

