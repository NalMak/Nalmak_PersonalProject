#include "stdafx.h"
#include "MainGame.h"
#include "Core.h"
#include "TitleScene.h"
#include "homeworkScene.h"

TimeManager* g_time;

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	Core::DestroyInstance();
}

void MainGame::ApplicationSetting()
{
	Core::Desc core;
	core.OBJECT_TAG_COUNT = 1;
	core.OBJECT_LAYER_COUNT = OBJECT_LAYER_MAX;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.windowMode = true;
	// all resource load in resource directory
	core.resourceDirectoryPath = L"../Resource";

	m_engine->Initialize(g_hInst, g_hWnd, &core);
}

void MainGame::SystemSetting()
{
	g_time = TimeManager::GetInstance();

	m_engine->ActivateCollisionByLayer(OBJECT_LAYER_DEFAULT, OBJECT_LAYER_BACKGROUND);
	m_engine->ActivateCollisionByLayer(OBJECT_LAYER_DEFAULT, OBJECT_LAYER_DEFAULT);

	m_engine->AddScene(L"title", Scene::Instantiate<TitleScene>());
	m_engine->AddScene(L"homework", Scene::Instantiate<homeworkScene>());


	m_engine->SetStartScene(L"title");
}

int MainGame::Run()
{
	m_engine = Core::GetInstance();

	ApplicationSetting();

	SystemSetting();

	MSG msg;
	try
	{
		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			m_engine->Run();
		}

		return (int)msg.wParam;
	}
	catch (Exception& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		assert(0);
		return 0;
	}
}
