#include "stdafx.h"
#include "MapTool_AnimationState.h"
#include "MapToolManager.h"


MapTool_AnimationState::MapTool_AnimationState()
{
}


MapTool_AnimationState::~MapTool_AnimationState()
{
}

void MapTool_AnimationState::Initialize()
{
}

void MapTool_AnimationState::EnterState()
{
	MapToolManager::GetInstance()->ActiveAnimationObject(true);
}

void MapTool_AnimationState::UpdateState()
{

}

void MapTool_AnimationState::ExitState()
{
	MapToolManager::GetInstance()->ActiveAnimationObject(false);
}

GameObject * MapTool_AnimationState::GetAnimationObject()
{
	return m_animObj;
}
