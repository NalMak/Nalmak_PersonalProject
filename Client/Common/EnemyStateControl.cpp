#include "stdafx.h"
#include "EnemyStateControl.h"
#include "EnemyState.h"




EnemyStateControl::EnemyStateControl(Desc * _desc)
	:StateControl(&StateControl::Desc())
{
}

EnemyStateControl::~EnemyStateControl()
{
}

void EnemyStateControl::Initialize()
{
	m_character = GetComponent<CharacterController>();
	m_info = GetComponent<BnS_Enemy>();
	m_animController = GetComponent<AnimationController>();
	auto cam = Core::GetInstance()->GetMainCamera()->GetComponent<BnS_MainCamera>();

	for (auto& state : m_stateList)
	{
		EnemyState* lynState = (EnemyState*)(state.second);
		lynState->m_character = m_character;
		lynState->m_info = m_info;
		lynState->m_bnsMainCam = cam;
		lynState->m_animController = m_animController;
	}
	StateControl::Initialize();
}

void EnemyStateControl::Update()
{
	DEBUG_LOG(L"Enemy Current State", GetCurStateString());
	StateControl::Update();
}
