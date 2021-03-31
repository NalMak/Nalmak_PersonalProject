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
	GetComponent<DebuggingMode>()->SetDebuggingMode(DEBUGGING_MODE::DEBUGGING_MODE_PICKING, false);
}

void MapTool_NavMeshState::UpdateState()
{
}

void MapTool_NavMeshState::ExitState()
{
}
