#pragma once

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "Nalmak_Include.h"
class DirectionalLight;
class GameObject;
class PointLight;
class Mesh;
class Material;
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
	bool GetDirectionalLightInfo(DirectionalLightInfo& _info);
	const vector<PointLight*>& GetPointLights() { return m_pointLights; }
	PointLight* GetPointLight(int _index) { return m_pointLights[_index]; }
	size_t GetPointLightCount() { return m_pointLights.size(); }
	bool IsSkyBoxRender() { return m_isSkyBoxRender; }
private:
	Mesh* m_skyBoxMesh;
	Material* m_skyBoxMtrl;
public:
	Mesh* GetSkyboxMesh();
	Material* GetSkyboxMaterial();
private:
	DirectionalLight* m_directionalLigth = nullptr;
	bool m_isSkyBoxRender = false;
	vector<PointLight*> m_pointLights;
};
#endif

