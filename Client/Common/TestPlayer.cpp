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
		m_transform->position += m_transform->GetForward() * dTime;
		//m_rigidBody->SetWorldPosition(m_transform->position);
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
