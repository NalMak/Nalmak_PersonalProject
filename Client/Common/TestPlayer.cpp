#include "stdafx.h"
#include "TestPlayer.h"


TestPlayer::TestPlayer(Desc* _desc)
{
}


TestPlayer::~TestPlayer()
{
}

void TestPlayer::Initialize()
{
	m_rigidBody = GetComponent<RigidBody>();
}

void TestPlayer::Update()
{

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_UP_ARROW))
	{
		m_rigidBody->SetVelocity({ 0,0,2 });
	}
}
