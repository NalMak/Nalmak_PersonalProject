#include "stdafx.h"
#include "MapTool_ObjectState.h"


MapTool_ObjectState::MapTool_ObjectState()
{
}


MapTool_ObjectState::~MapTool_ObjectState()
{
}

void MapTool_ObjectState::Initialize()
{
}

void MapTool_ObjectState::EnterState()
{
	GetComponent<DebuggingMode>()->SetDebuggingMode(DEBUGGING_MODE::DEBUGGING_MODE_PICKING, true);
}

void MapTool_ObjectState::UpdateState()
{
}

void MapTool_ObjectState::ExitState()
{
}
