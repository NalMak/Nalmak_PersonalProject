#include "DebuggingMode.h"
#include "RenderManager.h"
#include "SystemInfo.h"
#include "CanvasRenderer.h"
#include "SingleImage.h"
#include "FreeMove.h"
#include "FreeMove.h"
#include "Core.h"
#include "Text.h"
#include "DirectoryMonitoring.h"
#include "InputManager.h"
#include "Transform.h"
DebuggingMode::DebuggingMode(Desc * _desc)
{
	m_input = nullptr;
	m_render = nullptr;
	m_debugLog = nullptr;
	m_debugCam = nullptr;
	m_mainCam = nullptr;
	m_grid = nullptr;
	m_debugModeDescObject = nullptr;
	m_pickingObj = nullptr;
	m_pickingOutLine = nullptr;
}

DebuggingMode::~DebuggingMode()
{
}

void DebuggingMode::Initialize()
{
	m_input = InputManager::GetInstance();
	m_render = RenderManager::GetInstance();

#pragma region Debug Desc
	Text::Desc text;
	text.boundary = { 0,0,1000,200 };
	text.color = D3DXCOLOR(0, 255, 0, 255);
	text.option = DT_LEFT | DT_WORDBREAK;
	text.height = 14;
	text.width = 7;
	auto debugDesc = INSTANTIATE()->AddComponent<Text>(&text)->AddComponent<CanvasRenderer>()->SetPosition(300, 0);
	m_debugModeDescObject = debugDesc->GetComponent<Text>();
#pragma endregion Debug Desc



#pragma region Debug Log
	m_debugLog = INSTANTIATE()->AddComponent<SystemInfo>();
#pragma endregion Debug Log


#pragma region Grid
	{
		MeshRenderer::Desc render;
		render.meshName = L"quadNoneNormal";
		render.mtrlName = L"SYS_Grid";
		m_grid = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetRotation(90, 0, 0)->SetScale(1000, 1000, 1000)->SetPosition(0,0.01f,0);
	}
#pragma endregion Grid
#pragma region Free Camera
	m_mainCam = RenderManager::GetInstance()->GetMainCamera()->GetGameObject();
	assert(L"Can't find main Cam" && m_mainCam);
	m_debugCam = INSTANTIATE(L"Free Camera")->AddComponent<Camera>()->AddComponent<FreeMove>()->AddComponent<DebugObject>();
	m_debugCam->SetActive(false);
#pragma endregion Free Camera
#pragma region RenderTarget
	auto rts = ResourceManager::GetInstance()->GetAllResource<RenderTarget>();
	int i = 0;
	for (auto& renderTarget : rts)
	{
		Text::Desc text;
		text.color = D3DXCOLOR(0, 255, 0, 255);
		text.text = renderTarget.second->GetName();
		text.boundary = { -100,-100,100,100 };
		auto rt = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>()->SetScale(200, 200)->AddComponent<Text>(&text);
		rt->GetComponent<SingleImage>()->SetTexture((((RenderTarget*)renderTarget.second))->GetTexture());
		int column = (i / 5);
		int row = i - column * 5;
		rt->SetPosition((float)(RenderManager::GetInstance()->GetWindowWidth() - (i / 5) * 200 - 100), row * 200.f + 100);
		m_renderTargets.emplace_back(rt);
		++i;
	}
#pragma endregion RenderTarget
	DirectoryMonitoring::Desc directory;
	directory.directoryPath = ResourceManager::GetInstance()->GetResourceDirectoryPath();
	INSTANTIATE()->AddComponent<DirectoryMonitoring>(&directory);

	MeshRenderer::Desc render;
	render.mtrlName = L"SYS_OutLine";
	auto obj = INSTANTIATE(L"OutLine")->AddComponent<MeshRenderer>(&render)->SetScale(0,0,0)->SetPosition(0,0,0)->AddComponent<DebugObject>();
	m_pickingOutLine = obj->GetComponent<MeshRenderer>();
	m_pickingOutLine->SetPickingEnable(false);

	m_debuggingMode.Off(DEBUGGING_MODE_RENDERTARGET);
	m_debuggingMode.On(DEBUGGING_MODE_FREE_CAMERA);
	m_debuggingMode.On(DEBUGGING_MODE_DEBUG_LOG);
	m_debuggingMode.Off(DEBUGGING_MODE_COLLIDER);
	m_debuggingMode.Off(DEBUGGING_MODE_PICKING);
	m_debuggingMode.On(DEBUGGING_MODE_GRID);
	m_debuggingMode.Off(DEBUGGING_MODE_TIME_PAUSE);


	CheckGridRender();
	CheckRenderTargetRender();
	CheckFreeCamera();
	CheckRecordDebugLog();
	CheckColliderRender();
	CheckPicking();
	CheckTimeStop();

	UpdateDesc();
}

void DebuggingMode::Update()
{
	if (m_input->GetKeyDown(KEY_STATE_F1))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_TIME_PAUSE);
		UpdateDesc();
		CheckTimeStop();
	}
	if (m_input->GetKeyDown(KEY_STATE_F2))
	{
		UpdateMaterial();
	}

	if (m_debuggingMode.Check(DEBUGGING_MODE_PICKING))
	{
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
		{
			GameObject* pickObj = Core::GetInstance()->PickObjectByMouse();

			if (pickObj)
			{
				if (m_pickingObj != pickObj)
				{
					if (m_pickingObj)
					{
						m_pickingObj->DeleteComponent<DebugObject>();
						m_pickingObj = nullptr;
					}
					m_pickingObj = pickObj;
					m_pickingObj->AddComponent<DebugObject>();
					Mesh* mesh = m_pickingObj->GetComponent<MeshRenderer>()->GetMesh();
					m_pickingOutLine->SetMesh(mesh);
					m_pickingOutLine->GetTransform()->SetScale(m_pickingObj->GetTransform()->scale);
					m_pickingOutLine->GetTransform()->SetParents(m_pickingObj);
					m_pickingOutLine->GetTransform()->SetPosition(0, 0, 0);
					m_pickingOutLine->GetTransform()->SetRotation(0, 0, 0);

				}
			}
			else if (m_pickingObj)
			{
				m_pickingObj->DeleteComponent<DebugObject>();
				m_pickingObj = nullptr;
				m_pickingOutLine->GetTransform()->SetScale(Vector3(0,0,0));
			}
		}
	}
	if (m_input->GetKeyDown(KEY_STATE_F4))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_GRID);
		UpdateDesc();
		CheckGridRender();
	}
	if (m_input->GetKeyDown(KEY_STATE_F5))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_PICKING);
		UpdateDesc();
		CheckPicking();
	}
	if (m_input->GetKeyDown(KEY_STATE_F6))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_RENDERTARGET);
		UpdateDesc();
		CheckRenderTargetRender();
	}
	if (m_input->GetKeyDown(KEY_STATE_F7))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_FREE_CAMERA);
		UpdateDesc();
		CheckFreeCamera();
	}
	if (m_input->GetKeyDown(KEY_STATE_F8))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_DEBUG_LOG);
		UpdateDesc();
		CheckRecordDebugLog();
		
	}
	if (m_input->GetKeyDown(KEY_STATE_F9))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_COLLIDER);
		UpdateDesc();
		CheckColliderRender();
	}

	

}

void DebuggingMode::ToggleMode(DEBUGGING_MODE _mode)
{
	if (m_debuggingMode.Check(_mode))
	{
		m_debuggingMode.Off(_mode);
	}
	else
	{
		m_debuggingMode.On(_mode);
	}
}

void DebuggingMode::CheckPicking()
{
	if (!m_debuggingMode.Check(DEBUGGING_MODE_PICKING))
	{
		if (m_pickingObj)
		{
			m_pickingObj->DeleteComponent<DebugObject>();
			m_pickingObj = nullptr;
		}
	}
}

void DebuggingMode::CheckFreeCamera()
{
	if (m_debuggingMode.Check(DEBUGGING_MODE_FREE_CAMERA))
	{
		m_mainCam->SetActive(false);
		m_debugCam->SetActive(true);
	}
	else
	{
		m_mainCam->SetActive(true);
		m_debugCam->SetActive(false);
	}
}

void DebuggingMode::CheckColliderRender()
{
	m_render->SetDebugRender(m_debuggingMode.Check(DEBUGGING_MODE_COLLIDER));
}

void DebuggingMode::CheckRecordDebugLog()
{
	m_debugLog->SetActive(m_debuggingMode.Check(DEBUGGING_MODE_DEBUG_LOG));
}

void DebuggingMode::CheckRenderTargetRender()
{
	bool isRTRender = m_debuggingMode.Check(DEBUGGING_MODE_RENDERTARGET);
	
	for (auto& rt : m_renderTargets)
	{
		rt->SetActive(isRTRender);
	}
}

void DebuggingMode::CheckGridRender()
{
	m_grid->SetActive(m_debuggingMode.Check(DEBUGGING_MODE_GRID));
}

void DebuggingMode::CheckTimeStop()
{
	if (m_debuggingMode.Check(DEBUGGING_MODE_TIME_PAUSE))
		TimeManager::GetInstance()->Pause();
	else
		TimeManager::GetInstance()->Resume();

}

void DebuggingMode::UpdateMaterial()
{
}

void DebuggingMode::UpdateDesc()
{
	wstring debugDesc;

	debugDesc += L"F1 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_TIME_PAUSE))
		debugDesc += L"(Pause)  ";
	else
		debugDesc += L"(Play) ";
	debugDesc += L"Time \n";

	debugDesc += L"F2 -  ";
	debugDesc += L"Update Material \n";


	debugDesc += L"F4 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_GRID))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off) ";
	debugDesc += L"Grid \n";

	debugDesc += L"F5 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_PICKING))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off) ";
	debugDesc += L"Picking \n";

	debugDesc += L"F6 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_RENDERTARGET))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off) ";
	debugDesc += L"RenderTarget \n";

	debugDesc += L"F7 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_FREE_CAMERA))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off) ";
	debugDesc += L"Free Camera \n";
	debugDesc += L"F8 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_DEBUG_LOG))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off)  ";
	debugDesc += L"Log \n";
	debugDesc += L"F9 -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_COLLIDER))
		debugDesc += L"(On)  ";
	else
		debugDesc += L"(Off) ";
	debugDesc += L"Collider \n";

	m_debugModeDescObject->SetText(debugDesc);
}
