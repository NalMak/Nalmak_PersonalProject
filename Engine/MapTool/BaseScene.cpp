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
	light.diffuseIntensity = 0.45f;
	light.ambientIntensity = 0.15f;
	light.color = { 1.f,0.9f,0.88f };
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(90, 0, 0);

	Camera::Desc camera;
	camera.zFar = 1000;
	auto cam = INSTANTIATE()->AddComponent<Camera>(&camera)->SetPosition(2, 1, -10.f);


	DebuggingMode::Desc debugDesc;
	debugDesc.freeCamera = true;
	auto debug = INSTANTIATE()->AddComponent<DebuggingMode>(&debugDesc)->AddComponent<StateControl>();
	debug->GetComponent<StateControl>()->AddState<MapTool_ObjectState>(L"object");
	debug->GetComponent<StateControl>()->AddState<MapTool_NavMeshState>(L"navMesh");
	debug->GetComponent<StateControl>()->AddState<MapTool_AnimationState>(L"animation");

	debug->GetComponent<StateControl>()->InitState(L"object");


	MapToolManager::GetInstance()->SetDebuggingMode(debug->GetComponent<DebuggingMode>());
	MapToolManager::GetInstance()->SetToolStateControl(debug->GetComponent<StateControl>());
}
