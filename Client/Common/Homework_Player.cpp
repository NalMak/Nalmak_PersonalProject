#include "stdafx.h"
#include "Homework_Player.h"


Homework_Player::Homework_Player(Desc * _desc)
{
}

Homework_Player::~Homework_Player()
{
}

void Homework_Player::Initialize()
{
	m_xAxis = 0;
	m_yAxis = 0;
}

void Homework_Player::Update()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_DOWN_ARROW))
	{
		m_transform->RotateAxis({ 1,0,0 }, dTime * 3);
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_UP_ARROW))
	{
		m_transform->RotateAxis({ -1,0,0 }, dTime * 3);
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_T))
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"Player2";
		mesh.mtrlName = L"test1";
		Animator::Desc anim;
		anim.meshName = L"Player2";
		auto obj = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<Animator>(&anim)->SetPosition(10, -10, 0)->SetScale(0.1f, 0.1f, 0.1f);
	}
	
	/*if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_DOWN_ARROW))
	{
		m_transform->position -= m_transform->GetUp() * 3 * dTime;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_UP_ARROW))
	{
		m_transform->position += m_transform->GetUp() * 3 * dTime;
	}*/

	//if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	//{
	//	m_transform->RotateAxis(m_transform->GetRight(), dTime * 3);
	//}
	//if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	//{
	//	m_transform->RotateAxis(m_transform->GetRight(), -dTime * 3);
	//}
	//if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	//{
	//	m_transform->RotateAxis(m_transform->GetUp(), dTime * 3);
	//}
	//if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	//{
	//	m_transform->RotateAxis(m_transform->GetUp(), -dTime * 3);
	//}
}
