#include "stdafx.h"
#include "MapTool_AnimationState.h"


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
	m_animObj = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>()->AddComponent<Animator>();
}

void MapTool_AnimationState::UpdateState()
{
}

void MapTool_AnimationState::ExitState()
{
	DESTROY(m_animObj);
}
