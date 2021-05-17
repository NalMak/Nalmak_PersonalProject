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
#include "DrawGizmo.h"

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
	m_pickingType = PICKING_TYPE_NONE;
	m_gizmoType = GIZMO_TYPE_POSITION;
	m_startOn_freeCamera = _desc->freeCamera;
	if (_desc->createDirectoryMonitor)
	{
		DirectoryMonitoring::Desc directory;
		directory.directoryPath = ResourceManager::GetInstance()->GetResourceDirectoryPath();
		m_directoryMonitor = INSTANTIATE()->AddComponent<DirectoryMonitoring>(&directory);
	}

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
	auto debugDesc = INSTANTIATE()->AddComponent<CanvasRenderer>()->SetPosition(300, 0)->AddComponent<Text>(&text);
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
		m_grid = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetRotation(90, 0, 0)->SetScale(1000, 1000, 1000)->SetPosition(0, 0.01f, 0);
		m_grid->GetComponent<MeshRenderer>()->SetPickingEnable(false);
	}
#pragma endregion Grid
#pragma region Free Camera
	m_mainCam = RenderManager::GetInstance()->GetMainCamera()->GetGameObject();
	assert(L"Can't find main Cam" && m_mainCam);
	m_debugCam = INSTANTIATE(0,0,L"Free Camera")->AddComponent<Camera>()->AddComponent<FreeMove>()->AddComponent<DebugObject>()->SetPosition(0,1,-5);
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

#pragma region OutLine
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"SYS_OutLine";
		auto obj = INSTANTIATE(L"OutLine")->AddComponent<MeshRenderer>(&render)->SetScale(0, 0, 0)->SetPosition(0, 0, 0);
		m_pickingOutLine = obj->GetComponent<MeshRenderer>();
		m_pickingOutLine->SetPickingEnable(false);
		m_pickingOutLine->SetActive(false);
	}
#pragma endregion OutLine
#pragma region Picking Gizmo
	{
		auto gizmo = INSTANTIATE()->AddComponent<DrawGizmo>();
		m_pickingGizmoBase  = gizmo->GetComponent<DrawGizmo>();
		m_pickingGizmoBase->SetActive(false);
		
	}
#pragma endregion Picking Gizmo


	m_debuggingMode.Off(DEBUGGING_MODE_RENDERTARGET);
	if(!m_startOn_freeCamera)
		m_debuggingMode.Off(DEBUGGING_MODE_FREE_CAMERA);
	else
		m_debuggingMode.On(DEBUGGING_MODE_FREE_CAMERA);

	m_debuggingMode.Off(DEBUGGING_MODE_FREE_CAMERA_ROCK);
	m_debuggingMode.On(DEBUGGING_MODE_DEBUG_LOG);
	m_debuggingMode.On(DEBUGGING_MODE_COLLIDER);
	m_debuggingMode.Off(DEBUGGING_MODE_PICKING);
	m_debuggingMode.On(DEBUGGING_MODE_GRID);
	m_debuggingMode.Off(DEBUGGING_MODE_TIME_PAUSE);


	CheckGridRender();
	CheckRenderTargetRender();
	CheckFreeCamera();
	CheckFreeCameraRock();
	CheckRecordDebugLog();
	CheckColliderRender();
	CheckPicking();
	CheckTimeStop();

	UpdateDesc();
}

void DebuggingMode::Update()
{


	if (m_input->GetKeyPress(KEY_STATE_ALT))
		return;

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
		if (m_input->GetKeyDown(KEY_STATE_1))
		{
			m_gizmoType = GIZMO_TYPE_POSITION;
			m_pickingGizmoBase->ChangeGizmoType(m_gizmoType);
		}
		if (m_input->GetKeyDown(KEY_STATE_2))
		{
			m_gizmoType = GIZMO_TYPE_ROTATION;
			m_pickingGizmoBase->ChangeGizmoType(m_gizmoType);
		}
		if (m_input->GetKeyDown(KEY_STATE_3))
		{
			m_gizmoType = GIZMO_TYPE_SCALE;
			m_pickingGizmoBase->ChangeGizmoType(m_gizmoType);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
		{
			PickObject();
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
		{
			m_pickingType = m_pickingGizmoBase->PickGizmo();
			if (m_pickingType != PICKING_TYPE_NONE)
				return;
		}
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			if (m_pickingObj)
			{
				if (m_pickingType != PICKING_TYPE_NONE)
				{
					UpdatePickingObject();
				}
			}
		}

		if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
		{
			m_pickingType = PICKING_TYPE_NONE;
		}
	}
	if (m_input->GetKeyDown(KEY_STATE_Z))
	{
		ToggleMode(DEBUGGING_MODE::DEBUGGING_MODE_FREE_CAMERA_ROCK);
		UpdateDesc();
		CheckFreeCameraRock();
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
	if (m_input->GetKeyDown(KEY_STATE_F11))
	{
		m_debugCam->SetPosition(0, 0, -10);
		m_debugCam->SetRotation(0, 0, 0);
	}
	
	//DEBUGGING_MODE_GIZMO
}


void  DebuggingMode::Release()
{
	m_event.Release();
};

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
			DeletePicking();
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

void DebuggingMode::CheckFreeCameraRock()
{
	if (m_debuggingMode.Check(DEBUGGING_MODE_FREE_CAMERA_ROCK))
	{
		m_debugCam->GetComponent<FreeMove>()->SetActive(false);
	}
	else
	{
		m_debugCam->GetComponent<FreeMove>()->SetActive(true);
	}
}

void DebuggingMode::CheckColliderRender()
{
	m_render->SetColliderRender(m_debuggingMode.Check(DEBUGGING_MODE_COLLIDER));
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
	{
		debugDesc += L"(On)  ";
		debugDesc += L"\n 1. Position \n";
		debugDesc += L" 2. Rotation \n";
		debugDesc += L" 3. Scale \n";
	}
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

	debugDesc += L"Z -  ";
	if (m_debuggingMode.Check(DEBUGGING_MODE_FREE_CAMERA_ROCK))
		debugDesc += L"(On)  ";
	else
	{
		debugDesc += L"(Off) ";
	}
	debugDesc += L"Camera Rock \n";

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
	debugDesc += L"F11 - Camera Reset";
	m_debugModeDescObject->SetText(debugDesc);
}

void DebuggingMode::PickObject()
{

	

	GameObject* pickObj = Core::GetInstance()->PickObjectByMouse(&Vector3());

	if (pickObj)
	{
		if (m_pickingObj != pickObj)
		{
			PickObject(pickObj);
		}
	}
	else 
	{
		if (m_pickingObj)
		{
			DeletePicking();
		}
		m_pickingObj = nullptr;
	}
}

void DebuggingMode::DeletePicking()
{
	if (IsValid(m_pickingObj))
	{
		m_pickingObj->DeleteComponent<DebugObject>();
		m_pickingOutLine->GetTransform()->SetScale(Vector3(0, 0, 0));

		m_pickingGizmoBase->GetTransform()->DeleteParent();
		m_pickingGizmoBase->SetActive(false);

		auto handler = m_event.GetHandler(0);
		if (handler)
			m_event.DoEvent(0);
	}
}

void DebuggingMode::UpdateOutLine()
{
	if (!m_pickingObj)
		return;

	m_pickingOutLine->GetTransform()->SetScale(m_pickingObj->GetTransform()->scale);
	m_pickingOutLine->GetTransform()->SetPosition(0, 0, 0);
	m_pickingOutLine->GetTransform()->SetRotation(0, 0, 0);
}

void DebuggingMode::UpdatePickingObject()
{

	auto handler = m_event.GetHandler(1);
	if (handler)
		m_event.DoEvent(1);

	Camera* currentCam;
	if (m_debuggingMode.Check(DEBUGGING_MODE_FREE_CAMERA))
		currentCam = m_debugCam->GetComponent<Camera>();
	else
		currentCam = m_mainCam->GetComponent<Camera>();

	Line l1, l2, result;
	Vector3 objPos = m_pickingObj->GetTransform()->GetWorldPosition();
	Vector3 dir;
	if (m_pickingType == PICKING_TYPE_RIGHT)
		dir = m_pickingObj->GetTransform()->GetRight();
	else if (m_pickingType == PICKING_TYPE_UP)
		dir = m_pickingObj->GetTransform()->GetUp();
	else if (m_pickingType == PICKING_TYPE_LOOK)
		dir = m_pickingObj->GetTransform()->GetForward();
	l1.start = objPos - dir * 1000;
	l1.end = objPos + dir * 1000;
	l2.start = currentCam->GetTransform()->GetWorldPosition();
	l2.end = l2.start + currentCam->GetCamToMouseWorldDirection() * 1000;
	float distance = Nalmak_Math::GetDistance_LineToLine(result, l1, l2);
	auto rigid = m_pickingObj->GetComponent<RigidBody>();

	switch (m_gizmoType)
	{
	case GIZMO_TYPE_POSITION:
	{
		float distance = Nalmak_Math::Distance(m_pickingObj->GetTransform()->GetWorldPosition(), RenderManager::GetInstance()->GetMainCamera()->GetTransform()->GetWorldPosition());

		m_pickingObj->SetPosition(result.start - dir * distance * 0.08f);
		if (rigid)
		{
			rigid->SetWorldPositionAndRotation(result.start - dir * distance * 0.08f, m_pickingObj->GetTransform()->GetWorldRotation());
			rigid->SetAngularVelocity({ 0,0,0 });
			rigid->SetVelocity({ 0,0,0 });
		}
		break;
	}
	case GIZMO_TYPE_ROTATION:
	{
		Vector3 rotDir = result.start - (m_pickingObj->GetTransform()->GetWorldPosition() + dir * 2);

		float ratio = Nalmak_Math::Length(rotDir) / Nalmak_Math::Length(dir) * 1.f;
		if (rotDir.x * dir.x < 0 || rotDir.y * dir.y < 0 || rotDir.z * dir.z < 0)
			ratio *= -1.f;
		Quaternion rot;
		D3DXQuaternionRotationAxis(&rot, &dir, dTime * ratio);
		m_pickingObj->GetTransform()->rotation *= rot;

		if (rigid)
		{
			rigid->SetWorldPositionAndRotation(m_pickingObj->GetTransform()->GetWorldPosition(), m_pickingObj->GetTransform()->rotation);
			rigid->SetAngularVelocity({ 0,0,0 });
			rigid->SetVelocity({ 0,0,0 });
		}
		break;
	}
	case GIZMO_TYPE_SCALE:
	{
		Vector3 scaleDir = result.start - (m_pickingObj->GetTransform()->GetWorldPosition() + dir * 2);

		float ratio = Nalmak_Math::Length(scaleDir) / Nalmak_Math::Length(dir) * 0.2f;
		if (scaleDir.x * dir.x < 0 || scaleDir.y * dir.y < 0 || scaleDir.z * dir.z < 0)
			ratio *= -1.f;


		if (m_pickingType == PICKING_TYPE_RIGHT)
		{
			if (m_pickingObj->GetTransform()->scale.x + dTime * ratio > 0)
				m_pickingObj->GetTransform()->scale.x += dTime * ratio;
		}
		else if (m_pickingType == PICKING_TYPE_UP)
		{
			if (m_pickingObj->GetTransform()->scale.y + dTime * ratio > 0)
				m_pickingObj->GetTransform()->scale.y += dTime * ratio;
		}
		else if (m_pickingType == PICKING_TYPE_LOOK)
		{
			if (m_pickingObj->GetTransform()->scale.z + dTime * ratio > 0)
				m_pickingObj->GetTransform()->scale.z += dTime * ratio;
		}

		UpdateOutLine();
		break;
	}
	default:
		break;
	}
}




void DebuggingMode::AddUpdateMaterialEvent(EventHandler _e)
{
#pragma region DirectoryMonitoring
	{
		DirectoryMonitoring::Desc directory;
		directory.changeMaterialEvent += _e;
		directory.directoryPath = ResourceManager::GetInstance()->GetResourceDirectoryPath();
		m_directoryMonitor = INSTANTIATE()->AddComponent<DirectoryMonitoring>(&directory);
	}
#pragma endregion DirectoryMonitoring
}

void DebuggingMode::PickObject(GameObject * _obj)
{
	if (IsValid(m_pickingObj))
	{
		if (m_pickingObj)
		{
			m_pickingObj->DeleteComponent<DebugObject>();
			m_pickingObj = nullptr;
		}
	}

	if (!_obj)
	{
		m_pickingGizmoBase->SetActive(false);
		m_pickingOutLine->SetActive(false);

		return;
	}

	m_pickingOutLine->SetActive(true);

	m_pickingObj = _obj;
	m_pickingObj->AddComponent<DebugObject>();

	auto handler = m_event.GetHandler(0);
	if (handler)
		m_event.DoEvent(0);

	m_pickingGizmoBase->GetTransform()->SetParents(_obj);
	m_pickingGizmoBase->GetTransform()->SetPosition(0, 0, 0);
	m_pickingGizmoBase->GetTransform()->rotation = { 0, 0, 0, 1 };

	m_pickingGizmoBase->SetActive(true);


	//m_pickingObj->GetComponent<DebugObject>()->SetEnablePicking();
	if (m_pickingObj->GetComponent<MeshRenderer>())
	{
		Mesh* mesh = m_pickingObj->GetComponent<MeshRenderer>()->GetMesh();
		m_pickingOutLine->SetMesh(mesh);
	}
	
	m_pickingOutLine->GetTransform()->SetParents(m_pickingObj);
	UpdateOutLine();
}

void DebuggingMode::AddEvent(EventHandler _e)
{
	m_event.AddHandler(_e);
}

GameObject * DebuggingMode::GetPickingObject()
{
	return m_pickingObj;
}

void DebuggingMode::SetDebugModeActive(DEBUGGING_MODE _mode, bool _active)
{
	if (_active)
		m_debuggingMode.On(_mode);
	else
		m_debuggingMode.Off(_mode);

	CheckGridRender();
	CheckRenderTargetRender();
	CheckFreeCamera();
	CheckRecordDebugLog();
	CheckColliderRender();
	CheckPicking();
	CheckTimeStop();

	UpdateDesc();
}

//void SetDebugModeActive(DEBUGGING_MODE _mode, bool _active)
//{
//	if(_active)
//		m_debuggingMode.On(_mode);
//	else
//		m_debuggingMode.Off(_mode);
//}
//
