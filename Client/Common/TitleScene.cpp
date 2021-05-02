#include "stdafx.h"
#include "TitleScene.h"
#include "TitleToStage.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	INSTANTIATE()->AddComponent<Camera>();


	SingleImage::Desc image;
	image.textureName = L"test";
	INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->AddComponent<TitleToStage>()->SetPosition(HALF_WINCX,HALF_WINCY)->SetScale(WINCX,WINCY);

}
