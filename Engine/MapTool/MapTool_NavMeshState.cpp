#include "stdafx.h"
#include "MapTool_NavMeshState.h"


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
		m_pickingPointsForDebug[i] = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetScale(0.22f,0.22f,0.22f);
		m_pickingPointsForDebug[i]->SetActive(false);
	}

	m_currentSelectAddPoints[0] = nullptr;
	m_currentSelectAddPoints[1] = nullptr;
}

void MapTool_NavMeshState::EnterState()
{
	GetComponent<DebuggingMode>()->SetDebugModeActive(DEBUGGING_MODE::DEBUGGING_MODE_PICKING, false);
}

void MapTool_NavMeshState::UpdateState()
{
	Vector2 mousePos = InputManager::GetInstance()->GetMousePosition();
	Vector3 pickingPoint = { 0,0,0 };

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		m_navMesh->Reset();

		m_currentSelectAddPoints[0] = nullptr;
		m_currentSelectAddPoints[1] = nullptr;
		m_pickingPointsForDebug[0]->SetActive(false);
		m_pickingPointsForDebug[1]->SetActive(false);

		for (auto& point : m_navMesh->GetPointList())
		{
			if(IsPickingSuccessNavPoint(point->position))
			{
				m_currentSelectMovePoint = point;
				return;
			}
		}
			
		m_currentSelectCell = nullptr;
		// 클릭이 된 셀을 얻어냄
		for (auto& cell : m_navMesh->GetCellList())
		{
			if(IsPickingSuccessNavPoint(cell->GetCenter()))
			{
				m_currentSelectCell = cell;
				break;
			}
		}
		m_navMesh->SetStartPosition(m_startPoint.position);
		m_navMesh->SetEndPosition(m_endPoint.position);
		m_navMesh->FindPath();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		// 선택된 점이 있다면
		if (m_currentSelectMovePoint)
		{
			if (Core::GetInstance()->PickObjectByMouse(&pickingPoint))
			{
				m_currentSelectMovePoint->position = pickingPoint;

				// 선택된 점 한개가 움직일경우 위치 변경
				if (m_currentSelectMovePoint == &m_startPoint || m_currentSelectMovePoint == &m_endPoint)
				{
					


				}
				m_navMesh->FindPath();

				m_navMesh->SetStartPosition(m_startPoint.position);
				m_navMesh->SetEndPosition(m_endPoint.position);

				m_navMesh->UpdateMapBoundaryLine();
			}
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
							m_navMesh->UpdateMapBoundaryLine();

							m_navMesh->FindPath();

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
						m_navMesh->UpdateMapBoundaryLine();

						m_navMesh->FindPath();
					}
				}
			}

		}
	
		
	}

	
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
