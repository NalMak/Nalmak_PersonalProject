#include "stdafx.h"
#include "PlayerIdle.h"


PlayerIdle::PlayerIdle()
{
}

PlayerIdle::~PlayerIdle()
{
}

void PlayerIdle::Initialize()
{
}

void PlayerIdle::EnterState()
{
}

void PlayerIdle::UpdateState()
{
	

	float speed = 4;
	if(InputManager::GetInstance()->GetKeyPress(KEY_STATE_T))
		GetComponent<CharacterController>()->Move(0, 0, speed * dTime);
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_G))
		GetComponent<CharacterController>()->Move(0,  0, -speed * dTime);
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_F))
		GetComponent<CharacterController>()->Move(-speed * dTime, 0, 0);
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_H))
		GetComponent<CharacterController>()->Move(speed * dTime, 0, 0);
	if (GetComponent<CharacterController>()->IsGround())
	{
		DEBUG_LOG(L"ground", L"ground");
	}
	else
	{
		GetComponent<CharacterController>()->Move(0, -9.8f * dTime, 0);
		DEBUG_LOG(L"no ground", L"no ground");
	}
}

void PlayerIdle::ExitState()
{
}
