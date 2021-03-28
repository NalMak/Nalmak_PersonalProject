#include "stdafx.h"
#include "BaseScene.h"


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
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f);

	INSTANTIATE()->AddComponent<DebuggingMode>();

}
