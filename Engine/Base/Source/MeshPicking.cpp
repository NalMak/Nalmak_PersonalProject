#include "MeshPicking.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "DrawGizmo.h"
#include "RenderManager.h"
#include "PositionHandle.h"
#include "InputManager.h"

MeshPicking::MeshPicking(Desc* _desc)
{
}


void MeshPicking::Initialize()
{
	m_mainCam = RenderManager::GetInstance()->GetMainCamera();

	m_renderer = GetComponent<VIBufferRenderer>();
	m_gizmo = GetComponent<DrawGizmo>();
	m_handle = GetComponent<PositionHandle>();
}

void MeshPicking::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (m_handle)
		{
			if (IsMousePicking())
			{
				m_handle->PickHandle(true);
			}
		}
		else if (m_gizmo)
		{
			if (!m_gizmo->CheckHandlePicked())
			{
				if (IsMousePicking())
				{
					m_gizmo->SetActiveHandles(true);
				}
			}
			else
			{
				m_gizmo->SetActiveHandles(false);
			}
		}
	}

	if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (m_handle)
		{
			m_handle->PickHandle(false);
		}
	}
}


bool MeshPicking::IsMousePicking()
{
	Matrix worldMat = m_transform->GetWorldMatrix();
	Vector3 rayPoint = m_mainCam->GetTransform()->GetWorldPosition();
	Vector3 rayDir = m_mainCam->GetCamToMouseWorldDirection();	// look

	Mesh* mesh =  ResourceManager::GetInstance()->GetResource<Mesh>(L"box");// = m_renderer->GetVIBuffer();
	int figureCount = mesh->GetFigureCount();
	Vector3* vertices = mesh->GetVertexPositionData();
	INDEX32* indices = mesh->GetIndices();

	/*for (int i = 0; i < figureCount * 3; i += 3)
	{
		Vector3 v0;
		Vector3 v1;
		Vector3 v2;
		D3DXVec3TransformCoord(&v0, &vertices[indices[i]].position, &worldMat);
		D3DXVec3TransformCoord(&v1, &vertices[indices[i + 1]].position, &worldMat);
		D3DXVec3TransformCoord(&v2, &vertices[indices[i + 2]].position, &worldMat);
		Vector3 intersectPoint;
		if (Nalmak_Math::IsIntersectTriangle(
			rayPoint,
			rayDir,
			v0,
			v1,
			v2,
			&intersectPoint))
		{
			return true;
		}
	}*/
	return false;
}
