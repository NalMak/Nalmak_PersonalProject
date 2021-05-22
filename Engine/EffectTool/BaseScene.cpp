#include "stdafx.h"
#include "BaseScene.h"
#include "StaticObjectInfo.h"


BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
}

void BaseScene::Initialize()
{
	wstring path = ResourceManager::GetInstance()->GetResourceDirectoryPath();
	wstring sceneName = L"stage";
	path += (L"/" + sceneName);
	//ResourceManager::GetInstance()->ReleaseSceneResouce();
	ResourceManager::GetInstance()->LoadAllResources(L"../../Client/Resource/", false);

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f);

	DebuggingMode::Desc debug;
	debug.createDirectoryMonitor = false;
	debug.freeCamera = true;
	debug.directoryMonitorPath = L"../../Client/Resource/stage/";
	INSTANTIATE()->AddComponent<DebuggingMode>(&debug);

	auto staticObj = ResourceManager::GetInstance()->GetAllResource<StaticObjectInfo>();
	for (auto& obj : staticObj)
		MAKE_STATIC(obj.first);
}
