#include "..\Include\PositionHandle.h"
#include "Transform.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"

PositionHandle::PositionHandle(Desc* _desc)
{
	m_moveDir = _desc->dir;

}


void PositionHandle::Initialize()
{
	m_input = InputManager::GetInstance();
	m_camera = RenderManager::GetInstance()->GetMainCamera();

	m_target = m_transform->GetParents();

	switch (m_moveDir)
	{
	case PositionHandle::RIGHT:
		m_transform->position = m_target->GetRight() * 3;
		break;
	case PositionHandle::UP:
		m_transform->position = m_target->GetUp() * 3;
		break;
	case PositionHandle::FORWARD:
		m_transform->position = m_target->GetForward() * 3;
		break;
	default:
		break;
	}

	m_gameObject->SetActive(false);
}

void PositionHandle::Update()
{
	if (m_isPick)
		MoveTarget();
}

void PositionHandle::MoveTarget()
{
	Vector2 dir = m_input->GetMouseMoveDir();
	if (Vector2(0.f, 0.f) == dir)
		return;

	Vector3 axis;

	switch (m_moveDir)
	{
	case PositionHandle::RIGHT:
		axis = m_target->GetRight();
		break;
	case PositionHandle::UP:
		axis = m_target->GetUp();
		break;
	case PositionHandle::FORWARD:
		axis = m_target->GetForward();
		break;
	default:
		break;
	}

	Vector2 targetWinPos = m_camera->WorldToScreenPos(m_target->position);
	Vector2 handleWinPos = m_camera->WorldToScreenPos(m_transform->position + m_target->position);

	D3DXVec2Normalize(&dir, &dir);

	if (fabsf(dir.x) > fabsf(dir.y))
	{
		// 화면에서 handle이 타겟 왼쪽 -> 역방향으로
		if (targetWinPos.x > handleWinPos.x)
			axis = -axis;

		axis *= dir.x;
	}
	else
	{
		// 화면에서 handle이 타겟 아래쪽 -> 역방향으로
		if (targetWinPos.y < handleWinPos.y)
			axis = -axis;

		axis *= dir.y;
	}
	Vector3 look = m_target->position - m_camera->GetTransform()->position;
	float len = D3DXVec3Length(&look) * 2.f;
	m_target->position += axis * len * dTime;
}
