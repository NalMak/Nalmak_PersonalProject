#include "..\Include\DrawGizmo.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PositionHandle.h"
#include "MeshRenderer.h"
#include "RenderManager.h"
#include "Camera.h"
#include "PhysicsManager.h"

DrawGizmo::DrawGizmo(Desc * _desc)
{
	MeshRenderer::Desc render;
	render.meshName = L"pyramid";
	render.mtrlName = L"SYS_Picking_Red";
	m_pickingGizmo[0] = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(2, 0, 0)->SetScale(0.3f, 0.3f, 0.3f)->SetRotation(0, 0, -90);

	render.mtrlName = L"SYS_Picking_Green";
	m_pickingGizmo[1] = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 2, 0)->SetScale(0.3f, 0.3f, 0.3f);
	
	render.mtrlName = L"SYS_Picking_Blue";
	m_pickingGizmo[2] = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 2)->SetScale(0.3f, 0.3f, 0.3f)->SetRotation(90, 0, 0);
}

DrawGizmo::~DrawGizmo()
{
}

void DrawGizmo::OnEnable()
{
	for (int i = 0; i < 3; ++i)
	{
		m_pickingGizmo[i]->SetActive(true);
	}
}

void DrawGizmo::OnDisable()
{
	for (int i = 0; i < 3; ++i)
	{
		m_pickingGizmo[i]->SetActive(false);
	}
}

void DrawGizmo::Initialize()
{
	m_line = LineManager::GetInstance();
	m_pickingGizmo[0]->SetParents(m_transform);
	m_pickingGizmo[1]->SetParents(m_transform);
	m_pickingGizmo[2]->SetParents(m_transform);

}

void DrawGizmo::Update()
{
	float distance = Nalmak_Math::Distance(m_transform->GetWorldPosition(), RenderManager::GetInstance()->GetMainCamera()->GetTransform()->GetWorldPosition());

	for (int i = 0; i < 3; ++i)
	{
		m_pickingGizmo[i]->SetScale(distance * 0.04f, distance * 0.04f, distance * 0.04f);
	}
	m_pickingGizmo[0]->SetPosition(distance * 0.08f, 0, 0);
	m_pickingGizmo[1]->SetPosition(0, distance *  0.08f, 0);
	m_pickingGizmo[2]->SetPosition(0, 0, distance *  0.08f);

}

void DrawGizmo::LateUpdate()
{
	Matrix world = m_transform->GetWorldMatrix();
	Vector3 pos = { world._41,world._42,world._43 };
	m_line->DrawLine(pos, pos + Vector3(world._11, world._12, world._13), DEBUG_COLOR_RED);		// right
	m_line->DrawLine(pos, pos + Vector3(world._21, world._22, world._23), DEBUG_COLOR_GREEN);	// up
	m_line->DrawLine(pos, pos + Vector3(world._31, world._32, world._33), DEBUG_COLOR_BLUE);	// forward

}

void DrawGizmo::ChangeGizmoType(GIZMO_TYPE _type)
{
	switch (_type)
	{
	case GIZMO_TYPE_POSITION:
		for (int i = 0; i < 3; ++i)
		{
			m_pickingGizmo[i]->GetComponent<MeshRenderer>()->SetMesh(L"pyramid");
		}
		break;
	case GIZMO_TYPE_ROTATION:
		for (int i = 0; i < 3; ++i)
		{
			m_pickingGizmo[i]->GetComponent<MeshRenderer>()->SetMesh(L"sphere");
		}
		break;
	case GIZMO_TYPE_SCALE:
		for (int i = 0; i < 3; ++i)
		{
			m_pickingGizmo[i]->GetComponent<MeshRenderer>()->SetMesh(L"box");
		}
		break;
	default:
		break;
	}
}

PICKING_TYPE DrawGizmo::PickGizmo()
{
	if (!IsActive())
		return PICKING_TYPE_NONE;

	Camera* cam = RenderManager::GetInstance()->GetMainCamera();
	Vector3 camPos = cam->GetTransform()->GetWorldPosition();
	Vector3 dir = cam->GetCamToMouseWorldDirection();

	vector<MeshRenderer*> renderList;
	for (int i = 0; i < 3; ++i)
		renderList.emplace_back(m_pickingGizmo[i]->GetComponent<MeshRenderer>());
	auto obj = PhysicsManager::GetInstance()->Raycast(&Vector3(), camPos, camPos + dir * 1000, renderList);

	if (obj)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (m_pickingGizmo[i] == obj)
			{
				return (PICKING_TYPE)i;
			}
		}
		return PICKING_TYPE::PICKING_TYPE_NONE;
	}
	else
		return PICKING_TYPE::PICKING_TYPE_NONE;
}
