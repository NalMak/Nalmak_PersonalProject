#include "..\Include\DrawGizmo.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PositionHandle.h"
#include "MeshRenderer.h"

DrawGizmo::DrawGizmo(Desc * _desc)
{
}

DrawGizmo::~DrawGizmo()
{
}

void DrawGizmo::Initialize()
{
	m_line = LineManager::GetInstance();

}

void DrawGizmo::Update()
{

}

void DrawGizmo::LateUpdate()
{
	Matrix world = m_transform->GetNoneScaleWorldMatrix();
	Vector3 pos = { world._41,world._42,world._43 };
	m_line->DrawLine(pos, pos + Vector3(world._11, world._12, world._13) * 2, DEBUG_COLOR_RED);		// right
	m_line->DrawLine(pos, pos + Vector3(world._21, world._22, world._23) * 2, DEBUG_COLOR_GREEN);	// up
	m_line->DrawLine(pos, pos + Vector3(world._31, world._32, world._33) * 2, DEBUG_COLOR_BLUE);	// forward

}
