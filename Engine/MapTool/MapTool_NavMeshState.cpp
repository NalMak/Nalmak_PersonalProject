#include "stdafx.h"
#include "MapTool_NavMeshState.h"


MapTool_NavMeshState::MapTool_NavMeshState()
{
}


MapTool_NavMeshState::~MapTool_NavMeshState()
{
}

void MapTool_NavMeshState::Initialize()
{
}

void MapTool_NavMeshState::EnterState()
{
	GetComponent<DebuggingMode>()->SetDebugModeActive(DEBUGGING_MODE::DEBUGGING_MODE_PICKING, false);
}

void MapTool_NavMeshState::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		Vector3 point;
		if (Core::GetInstance()->PickObjectByMouse(&point))
		{
			INSTANTIATE()->AddComponent<MeshRenderer>()->SetPosition(point)->SetScale(0.1f,0.1f,0.1f);
		}
	}
	
}

void MapTool_NavMeshState::ExitState()
{
}
