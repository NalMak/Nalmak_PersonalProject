#include "stdafx.h"
#include "MapTool_NavMeshState.h"
#include "NavPointDraw.h"
#include "NavSelectedPoint.h"

MapTool_NavMeshState::MapTool_NavMeshState()
{
}


MapTool_NavMeshState::~MapTool_NavMeshState()
{
}

void MapTool_NavMeshState::Initialize()
{
	auto obj = INSTANTIATE()->AddComponent<NavMesh>();
	m_navMesh = obj->GetComponent<NavMesh>();

	MeshRenderer::Desc render;
	render.meshName = L"sphere";
	render.mtrlName = L"SYS_Diffuse_Red";
	for (int i = 0; i < 2; ++i)
	{
		m_pickingPointsForDebug[i] = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetScale(0.22f,0.22f,0.22f)->AddComponent<NavSelectedPoint>();
		m_pickingPointsForDebug[i]->SetActive(false);
	}

	m_currentSelectAddPoints[0] = nullptr;
	m_currentSelectAddPoints[1] = nullptr;


	render.mtrlName = L"SYS_Diffuse_Blue";
	m_startPoint = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetScale(0.3f, 0.3f, 0.3f);
	m_endPoint = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetScale(0.3f, 0.3f, 0.3f);
	m_startPoint->GetComponent<MeshRenderer>()->SetPickingEnable(false);
	m_endPoint->GetComponent<MeshRenderer>()->SetPickingEnable(false);

	m_pickModeGizmo = true;
}

void MapTool_NavMeshState::EnterState()
{
	//GetComponent<DebuggingMode>()->SetDebugModeActive(DEBUGGING_MODE::DEBUGGING_MODE_PICKING, false);

}

void MapTool_NavMeshState::UpdateState()
{
	Vector2 mousePos = InputManager::GetInstance()->GetMousePosition();
	Vector3 pickingPoint = { 0,0,0 };
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		m_pickModeGizmo ^= true;

		if (m_pickModeGizmo)
		{
			for (auto& point : m_pointDebug)
				point->GetComponent<MeshRenderer>()->SetPickingEnable(false);
		}
		else
		{
			for (auto& point : m_pointDebug)
				point->GetComponent<MeshRenderer>()->SetPickingEnable(true);
		}
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_X))
	{

	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{

		m_currentSelectAddPoints[0] = nullptr;
		m_currentSelectAddPoints[1] = nullptr;

		m_pickingPointsForDebug[0]->SetActive(false);
		m_pickingPointsForDebug[1]->SetActive(false);

		if (m_pickModeGizmo)
		{
			vector<MeshRenderer*> pointRenderer;
			for (auto& point : m_pointDebug)
				pointRenderer.emplace_back(point->GetComponent<MeshRenderer>());
			GameObject* pickPoint = Core::GetInstance()->PickObjectByMouse(nullptr, pointRenderer);
			if (pickPoint)
				m_currentSelectMovePoint = pickPoint;
		}

		vector<MeshRenderer*> centerRenderer;
		for (auto& cell : m_cellCenterDebug)
			centerRenderer.emplace_back(cell->GetComponent<MeshRenderer>());
		GameObject* pickCenter = Core::GetInstance()->PickObjectByMouse(nullptr, centerRenderer);
		if (pickCenter)
			pickCenter->GetComponent<NavPointDraw>()->ReverseCell();
		
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		if (Core::GetInstance()->PickObjectByMouse(&pickingPoint))
		{
			// 선택된 점이 있다면
			if (m_currentSelectMovePoint)
				m_currentSelectMovePoint->GetTransform()->SetPosition(pickingPoint);
		}
	}
	if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		m_currentSelectMovePoint = nullptr;
		
	}
	int notContactCount = 0;

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		m_currentSelectMovePoint = nullptr;

		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_ALT))
			return;

		if (Core::GetInstance()->PickObjectByMouse(&pickingPoint))
		{
			if (m_navMesh->GetPointList().size() == 0)
			{
				m_navMesh->CreateFirstPoint(pickingPoint);
			}
			else if (m_navMesh->GetPointList().size() == 1)
			{
				m_navMesh->CreateSecondPoint(pickingPoint);
			}
			else if (m_navMesh->GetPointList().size() == 2)
			{
				m_navMesh->CreateThirdPoint(pickingPoint);
			}
			else
			{
				//////////////////////////////////////////
				//
				// 우클릭시 정점 3개가 모인다면 셀을 생성시킴
				//
				for (auto& point : m_navMesh->GetPointList())
				{
					if (IsPickingSuccessNavPoint(point->position))
					{
						if (m_currentSelectAddPoints[0] == point)
						{
							m_currentSelectAddPoints[0] = nullptr;
							m_pickingPointsForDebug[0]->SetActive(false);

							break;
						}
						else if (m_currentSelectAddPoints[1] == point)
						{
							m_currentSelectAddPoints[1] = nullptr;
							m_pickingPointsForDebug[1]->SetActive(false);
							break;
						}

						if (m_currentSelectAddPoints[0] == nullptr)
						{
							m_currentSelectAddPoints[0] = point;
							m_pickingPointsForDebug[0]->SetActive(true);
							m_pickingPointsForDebug[0]->SetPosition(m_currentSelectAddPoints[0]->position);
						}
						else if (m_currentSelectAddPoints[1] == nullptr)
						{
							m_currentSelectAddPoints[1] = point;
							m_pickingPointsForDebug[1]->SetActive(true);
							m_pickingPointsForDebug[1]->SetPosition(m_currentSelectAddPoints[1]->position);
						}
						else // 세 점이 이미 만들어진 점으로 셀을 만들경우
						{
							m_navMesh->AddCell(point, m_currentSelectAddPoints[0], m_currentSelectAddPoints[1]);
							m_currentSelectAddPoints[0] = nullptr;
							m_currentSelectAddPoints[1] = nullptr;
							m_pickingPointsForDebug[0]->SetActive(false);
							m_pickingPointsForDebug[1]->SetActive(false);
						}
						break;
					}
					else
					{
						++notContactCount;
					}
				}
				// 이미 있던 두점과 새로운점 하나가 셀을 만들 경우
				if (notContactCount == m_navMesh->GetPointList().size())
				{
					if (m_currentSelectAddPoints[0] != nullptr && m_currentSelectAddPoints[1] != nullptr)
					{
						bool validPoint = false;
						for (auto& cell : m_currentSelectAddPoints[0]->GetParentCells())
						{
							for (int i = 0; i < 3; ++i)
							{
								if (cell->GetPoints()[i] == m_currentSelectAddPoints[1])
								{
									validPoint = true;
								}
							}
							if (validPoint)
								break;
						}
						if (!validPoint)
							return;

						NavPoint* newPoint = new NavPoint(pickingPoint.x, pickingPoint.y, pickingPoint.z);

						m_navMesh->AddCell(newPoint, m_currentSelectAddPoints[0], m_currentSelectAddPoints[1]);
						m_currentSelectAddPoints[0] = nullptr;
						m_currentSelectAddPoints[1] = nullptr;
						m_pickingPointsForDebug[0]->SetActive(false);
						m_pickingPointsForDebug[1]->SetActive(false);

					}
				}
			}

		}
	}

	DrawDebugObject();


	
}

void MapTool_NavMeshState::ExitState()
{
}

bool MapTool_NavMeshState::IsPickingSuccessNavPoint(Vector3  _point)
{
	auto cam = Core::GetInstance()->GetMainCamera();
	Vector3 dir = cam->GetCamToMouseWorldDirection();

	Line line;
	line.start = cam->GetTransform()->GetWorldPosition();
	line.end = line.start + dir;
	float distance = Nalmak_Math::GetDistance_PointToInfinityLine(_point, line);
	if (distance < m_navPointRadius)
	{
		return true;
	}

	return false;
}

void MapTool_NavMeshState::SetNavMesh(NavMesh * _navMesh)
{
	m_navMesh = _navMesh;
}


NavMesh * MapTool_NavMeshState::GetNavMesh()
{
	return m_navMesh;
}

void MapTool_NavMeshState::DrawDebugObject()
{
	AddDebugPoint();
	AddDebugCenter();


	Core* core = Core::GetInstance();
	for (auto& line : m_navMesh->GetLineList())
	{
		core->DrawLine(line->GetPoint()[0]->position, line->GetPoint()[1]->position);
	}
}

void MapTool_NavMeshState::AddDebugPoint()
{
	if (m_navMesh->GetPointList().size() > m_pointDebug.size())
	{
		for (size_t i = m_pointDebug.size(); i < m_navMesh->GetPointList().size(); ++i)
		{
			NavPointDraw::Desc point;
			point.navPoint = m_navMesh->GetPointList()[i];
			auto sphere = INSTANTIATE()->AddComponent<NavPointDraw>(&point)->SetPosition(point.navPoint->position);
			m_pointDebug.emplace_back(sphere);
		}
		

	}
}

void MapTool_NavMeshState::AddDebugCenter()
{
	if (m_navMesh->GetCellList().size() > m_cellCenterDebug.size())
	{
		for (size_t i = m_cellCenterDebug.size(); i < m_navMesh->GetCellList().size(); ++i)
		{
			NavPointDraw::Desc point;
			point.navCell = m_navMesh->GetCellList()[i];
		
			auto sphere = INSTANTIATE()->AddComponent<NavPointDraw>(&point)->SetPosition(m_navMesh->GetCellList()[i]->GetCenter());
			m_cellCenterDebug.emplace_back(sphere);

			AddDebugCenter();
		}
	}
}
