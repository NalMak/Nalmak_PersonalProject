#include "stdafx.h"
#include "BaseScene.h"
#include "MapToolManager.h"
#include "MapTool_ObjectState.h"
#include "MapTool_NavMeshState.h"
#include "MapTool_AnimationState.h"


BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
}

void BaseScene::Initialize()
{


	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.1f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f);


	auto debug = INSTANTIATE()->AddComponent<DebuggingMode>()->AddComponent<StateControl>();
	debug->GetComponent<StateControl>()->AddState<MapTool_ObjectState>(L"object");
	debug->GetComponent<StateControl>()->AddState<MapTool_NavMeshState>(L"navMesh");
	debug->GetComponent<StateControl>()->AddState<MapTool_AnimationState>(L"animation");

	debug->GetComponent<StateControl>()->InitState(L"object");

	MapToolManager::GetInstance()->SetDebuggingMode(debug->GetComponent<DebuggingMode>());
	MapToolManager::GetInstance()->SetToolStateControl(debug->GetComponent<StateControl>());
}
