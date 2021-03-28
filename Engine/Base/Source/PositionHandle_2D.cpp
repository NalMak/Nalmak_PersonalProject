#include "..\Include\PositionHandle_2D.h"
#include "Transform.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "CanvasRenderer.h"
#include "DrawGizmo_2D.h"


PositionHandle_2D::PositionHandle_2D(Desc * _desc)
{
	m_moveDir = _desc->dir;
	m_target = _desc->target;
}

void PositionHandle_2D::Initialize()
{
	m_input = InputManager::GetInstance();

	//m_target = m_transform->GetParents();

	switch (m_moveDir)
	{
	case PositionHandle_2D::RIGHT:
		m_transform->position = m_target->position + m_target->GetRight() * m_target->scale.x * 0.6f;
		break;
	case PositionHandle_2D::UP:
		m_transform->position = m_target->position + m_target->GetUp() * m_target->scale.y * 0.6f;
		break;
	default:
		break;
	}

	m_gameObject->SetActive(false);
}

void PositionHandle_2D::Update()
{
	if (m_isPick)
		MoveTarget();
}

void PositionHandle_2D::MoveTarget()
{
	Vector2 dir = m_input->GetMouseMoveDir();
	if (Vector2(0.f, 0.f) == dir)
		return;

	Vector3 axis;
	float len = D3DXVec2Length(&dir);
	D3DXVec2Normalize(&dir, &dir);

	switch (m_moveDir)
	{
	case PositionHandle_2D::RIGHT:
		axis = m_target->GetRight();
		axis *= dir.x;
		break;
	case PositionHandle_2D::UP:
		axis = m_target->GetUp();
		axis *= dir.y;
		break;
	default:
		break;
	}

	m_target->position += axis * len;
	
	m_target->GetComponent<DrawGizmo_2D>()->ResetingHandlePosition();
}

void PositionHandle_2D::ResetingPosition()
{
	switch (m_moveDir)
	{
	case PositionHandle_2D::RIGHT:
		m_transform->position = m_target->position + m_target->GetRight() * m_target->scale.x * 0.6f;
		break;
	case PositionHandle_2D::UP:
		m_transform->position = m_target->position + m_target->GetUp() * m_target->scale.y * 0.6f;
		break;
	default:
		break;
	}
}

bool PositionHandle_2D::CheckPicked()
{
	return GetComponent<CanvasRenderer>()->IsCursorOnRect();
}
