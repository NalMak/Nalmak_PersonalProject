#pragma once

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "Nalmak_Include.h"
class DirectionalLight;
class GameObject;
class PointLight;
class Mesh;
class Material;
class Camera;

class LightManager
{
	DECLARE_SINGLETON(LightManager)
private:
	LightManager();
	~LightManager();
public:
	void Initialize();
	void SetSkyBox(const wstring& _skyBoxName);
	void ResetSkyBox();
	void SetDirectionalLightInfo(DirectionalLight* _light);
	void DeleteDirectionalLight();
	void DeletePointLight(PointLight* _light);
	void AddPointLight(PointLight* _light);
	const DirectionalLightInfo& GetDirectionalLightInfo();
	bool IsExistDirectionalLight();
	const vector<PointLight*>& GetPointLights() { return m_pointLights; }
	PointLight* GetPointLight(int _index) { return m_pointLights[_index]; }
	DirectionalLight* GetDirectionalLight() { return m_directionalLight; }
	size_t GetPointLightCount() { return m_pointLights.size(); }
	bool IsSkyBoxRender() { return m_isSkyBoxRender; }
	Camera* GetLightCamera();
private:
	Mesh* m_skyBoxMesh;
	Material* m_skyBoxMtrl;
public:
	Mesh* GetSkyboxMesh();
	Material* GetSkyboxMaterial();
private:
	DirectionalLight* m_directionalLight = nullptr;
	bool m_isSkyBoxRender = false;
	vector<PointLight*> m_pointLights;
};
#endif

