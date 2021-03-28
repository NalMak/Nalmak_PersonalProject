#include "..\Include\ScaleHandle_2D.h"

#include "Transform.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "CanvasRenderer.h"
#include "DrawGizmo_2D.h"


ScaleHandle_2D::ScaleHandle_2D(Desc * _desc)
{
	m_moveDir = _desc->dir;
	m_target = _desc->target;
}

void ScaleHandle_2D::Initialize()
{
	m_input = InputManager::GetInstance();

	//m_target = m_transform->GetParents();

	switch (m_moveDir)
	{
	case ScaleHandle_2D::RIGHT:
		m_transform->position = m_target->position + m_target->GetRight() * m_target->scale.x * 0.6f;
		break;
	case ScaleHandle_2D::UP:
		m_transform->position = m_target->position + m_target->GetUp() * m_target->scale.y * 0.6f;
		break;
	default:
		break;
	}

	m_gameObject->SetActive(false);
}

void ScaleHandle_2D::Update()
{
	if (m_isPick)
		ScalingTarget();
}

void ScaleHandle_2D::ScalingTarget()
{
	Vector2 dir = m_input->GetMouseMoveDir();
	if (Vector2(0.f, 0.f) == dir)
		return;

	Vector3 axis;
	float len = D3DXVec2Length(&dir);
	D3DXVec2Normalize(&dir, &dir);

	switch (m_moveDir)
	{
	case ScaleHandle_2D::RIGHT:
		axis = m_target->GetRight();
		axis *= dir.x;
		break;
	case ScaleHandle_2D::UP:
		axis = m_target->GetUp();
		axis *= dir.y;
		break;
	default:
		break;
	}

	m_target->scale += axis * len;

	m_target->GetComponent<DrawGizmo_2D>()->ResetingHandlePosition();
}

void ScaleHandle_2D::ResetingPosition()
{
	switch (m_moveDir)
	{
	case ScaleHandle_2D::RIGHT:
		m_transform->position = m_target->position + m_target->GetRight() * m_target->scale.x * 0.6f;
		break;
	case ScaleHandle_2D::UP:
		m_transform->position = m_target->position + m_target->GetUp() * m_target->scale.y * 0.6f;
		break;
	default:
		break;
	}
}

bool ScaleHandle_2D::CheckPicked()
{
	return GetComponent<CanvasRenderer>()->IsCursorOnRect();
}
