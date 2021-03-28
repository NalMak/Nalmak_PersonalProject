#include "..\Include\DrawGizmo.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MeshPicking.h"
#include "PositionHandle.h"
#include "MeshRenderer.h"

DrawGizmo::DrawGizmo(Desc * _desc)
{
}

DrawGizmo::~DrawGizmo()
{
}

void DrawGizmo::SetActiveHandles(bool _value)
{
	m_rightHandle->SetActive(_value);
	m_upHandle->SetActive(_value);
	m_forwardHandle->SetActive(_value);
}

bool DrawGizmo::CheckHandlePicked()
{
	if (m_forwardHandle->GetComponent<PositionHandle>()->CheckPicked())
		return true;

	if (m_rightHandle->GetComponent<PositionHandle>()->CheckPicked())
		return true;

	if (m_upHandle->GetComponent<PositionHandle>()->CheckPicked())
		return true;

	return false;
}


void DrawGizmo::Initialize()
{
	m_line = LineManager::GetInstance();

	MeshRenderer::Desc desc_mr;
	PositionHandle::Desc desc_ph;

	desc_mr.meshName = L"box";
	desc_mr.mtrlName = L"default_red";
	desc_ph.dir = PositionHandle::RIGHT;
	m_rightHandle =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&desc_mr)->
		AddComponent<MeshPicking>()->
		AddComponent<PositionHandle>(&desc_ph)->
		SetScale(0.2f, 0.2f, 0.2f);
	m_rightHandle->SetParents(m_gameObject);

	desc_mr.mtrlName = L"default_green";
	desc_ph.dir = PositionHandle::UP;
	m_upHandle =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&desc_mr)->
		AddComponent<MeshPicking>()->
		AddComponent<PositionHandle>(&desc_ph)->
		SetScale(0.2f, 0.2f, 0.2f);
	m_upHandle->SetParents(m_gameObject);

	desc_mr.mtrlName = L"default_blue";
	desc_ph.dir = PositionHandle::FORWARD;
	m_forwardHandle =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&desc_mr)->
		AddComponent<MeshPicking>()->
		AddComponent<PositionHandle>(&desc_ph)->
		SetScale(0.2f, 0.2f, 0.2f);
	m_forwardHandle->SetParents(m_gameObject);
}

void DrawGizmo::Update()
{

}

void DrawGizmo::LateUpdate()
{
	Matrix world = m_transform->GetNoneScaleWorldMatrix();
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._11, world._12, world._13), DEBUG_COLOR_RED);		// right
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._21, world._22, world._23), DEBUG_COLOR_GREEN);	// up
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._31, world._32, world._33), DEBUG_COLOR_BLUE);	// forward

}
