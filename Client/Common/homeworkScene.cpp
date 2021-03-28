#include "stdafx.h"
#include "homeworkScene.h"
#include "Homework_Player.h"
#include "homework_enemy.h"

homeworkScene::homeworkScene()
{
}


homeworkScene::~homeworkScene()
{
}

void homeworkScene::Initialize()
{
	INSTANTIATE()->AddComponent<Camera>()->SetPosition(0,0,-3);



	MeshRenderer::Desc render;
	render.meshName = L"quad";
	render.mtrlName = L"default_red";
	auto player = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->AddComponent<Homework_Player>();

	render.meshName = L"triangle";
	render.mtrlName = L"default_green";
	homework_enemy::Desc enemy;
	enemy.target = player;
	INSTANTIATE()->AddComponent<MeshRenderer>(&render)->AddComponent<homework_enemy>(&enemy);
}
