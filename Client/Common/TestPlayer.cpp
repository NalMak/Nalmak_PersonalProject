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
		GetComponent<AnimationController>()->SetBool("attackEnd", true);
	}
}

void TestPlayer::OnCollisionEnter(Collisions & _col)
{
	DEBUG_LOG(L"Enter", L"Enter");
}

void TestPlayer::OnCollisionStay(Collisions & _col)
{
	DEBUG_LOG(L"Stay", L"Stay");
}

void TestPlayer::OnCollisionExit(Collisions & _col)
{
	DEBUG_LOG(L"Exit", L"Exit");
}
