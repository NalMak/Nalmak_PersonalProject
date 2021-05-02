#include "stdafx.h"
#include "TitleToStage.h"


TitleToStage::TitleToStage(Desc * _desc)
{
}

TitleToStage::~TitleToStage()
{
}

void TitleToStage::Initialize()
{
	
}

void TitleToStage::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_ENTER))
	{
		GetComponent<SingleImage>()->SetTexture(L"loading");
		Core::GetInstance()->LoadScene(L"stage", SCENE_LOAD_TYPE_THREAD);
	}
}
