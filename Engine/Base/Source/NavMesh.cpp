#include "NavMesh.h"

#include "NavCell.h"
#include "NavPoint.h"
#include "NavLine.h"
#include "MeshRenderer.h"
#include "LineManager.h"

NavMesh::NavMesh(Desc * _desc)
{
	
}


void NavMesh::Initialize()
{
}

void NavMesh::Update()
{
	//for (auto& cell : m_CellList)
	//{
	//	cell->Update();
	//}
}

bool NavMesh::FindPath()
{
	// 길 찾기전 저장했던 자료구조 초기화
	Reset();

	// 1단계
	// Astar알고리즘을 통해 최적의 셀을 찾아냄  
	// 만약 길이 없다면 초기탈출
	if (false == FindAstarPath())
		return false;

	// 2단계
	// 각 셀의 무게중심을 길으로 한 최적화된 길을 구함
	FindOptimalPath();

	// 3단계
	// 각 셀의 꼭지점까지 포함한 최적화된 길을 구함
	FindOptimalPath2();

	return true;
}

void NavMesh::RecordAstarPath(NavCell * _cell)
{
	m_AstarResultCells.push(_cell);

	if (nullptr != _cell->GetParent())
		RecordAstarPath(_cell->GetParent());
}

bool NavMesh::FindAstarPath()
{
	for (auto& cell : m_CellList)
	{
		cell->Reset();
		cell->Update();
	}
	// 시작 점이 셀 밖에 있을 시
	if (nullptr == m_startCell)
	{
		return false;
	}
	// 끝 점이 셀 밖에 있을 시
	else if (nullptr == m_endCell)
	{
		return false;
	}
	// 한 셀에 시작점과 끝점이 있을시
	if (m_startCell == m_endCell)
		return true;

	m_openList.clear();
	m_openList.emplace_back(m_startCell);
	bool bProcess = true;
	while (bProcess)
	{
		if (m_openList.empty())
			return false;

		// 코스트가 낮은 순으로 정렬 -> 최적화 필요
		sort(m_openList.begin(), m_openList.end(), [](NavCell* _a, NavCell* _b)->bool {return _a->GetCost() > _b->GetCost() ? true : false; });
		NavCell* currentCell = m_openList.back();
		m_openList.pop_back();

		currentCell->SetState(CELL_STATE::CELL_STATE_INVALID);

		for (int i = 0; i < 3; ++i)
		{
			NavCell* adjacentCell = currentCell->GetAdjacentCells()[i];

			if (nullptr == adjacentCell)
				continue;

			if (adjacentCell->GetState() != CELL_STATE::CELL_STATE_INVALID)
			{
				adjacentCell->SetParent(currentCell);
				adjacentCell->g = currentCell->g + Nalmak_Math::Distance(currentCell->GetCenter(), adjacentCell->GetCenter());
				m_openList.emplace_back(adjacentCell);
			}
		}

		for (auto& cell : m_openList)
		{
			if (cell == m_endCell)
			{
				bProcess = false;
			}
		}
	}
	RecordAstarPath(m_endCell);
	return true;
}

void NavMesh::FindOptimalPath()
{
	if (m_startCell == m_endCell) // 시작점과 끝점이 같은 셀일 경우 조기 탈출
	{
		m_OptimalPathPoint.emplace_back(m_startPos);
		m_OptimalPathPoint.emplace_back(m_endPos);

		return;
	}

	m_OptimalPathPoint.emplace_back(m_startPos);

	// 시작 셀을 둘러싼 외곽 라인을 구함
	m_AstarBoundaryLines.emplace_back(m_startCell->GetLines()[0]);
	m_AstarBoundaryLines.emplace_back(m_startCell->GetLines()[1]);
	m_AstarBoundaryLines.emplace_back(m_startCell->GetLines()[2]);


	NavCell* oldPathCell = m_startCell; // 이전에 탐색한 경로를 저장함
	bool roop = true;
	while (true)
	{
		if (m_AstarResultCells.empty())
			break;
		NavCell* currentCell = m_AstarResultCells.top(); // A*로 검색한 셀중 시작점에서부터 꺼내옴

		bool interSection = false;

		bool shortestPath = true;
		for (auto& boundaryLine : m_MapBoundaryLines) // 마지막 경로에서 한번에 끝지점까지 갈 수 있나 확인
		{
			if (Nalmak_Math::IsIntersectLineToLineOn2D(m_OptimalPathPoint.back(), m_endPos,
				(boundaryLine->GetPoint()[0])->position, (boundaryLine->GetPoint()[1])->position))
			{
				shortestPath = false;
				break;
			}
		}
		if (shortestPath)
		{
			m_OptimalPathPoint.emplace_back(m_endPos);
			return;
		}

		for (auto& boundaryLine : m_AstarBoundaryLines)
		{
			// 셀의 중점과 판단할 점으로 이루어진 선분과  외곽 라인들과 교점이있는지 판단
			if (Nalmak_Math::IsIntersectLineToLineOn2D(m_OptimalPathPoint.back(), currentCell->GetCenter(),
				(boundaryLine->GetPoint()[0])->position, (boundaryLine->GetPoint()[1])->position))
				interSection = true;
		}
		if (interSection) // 교점이 존재한다면
		{
			if (false == roop) // 더 이상 경로가 없을 때 (interSection 이 연속해서 호출됨) -> 셀의 중점에서 중점으로 가는 길이 없을때
			{
				m_OptimalPathPoint.clear();
				return;
			}
			roop = false;

			m_OptimalPathPoint.emplace_back(oldPathCell->GetCenter()); // 전에 검색한 점을 경로로 지정
			m_OptimalPathCell.emplace_back(oldPathCell);
			m_AstarBoundaryLines.clear();
			m_AstarBoundaryLines.emplace_back(oldPathCell->GetLines()[0]);
			m_AstarBoundaryLines.emplace_back(oldPathCell->GetLines()[1]);
			m_AstarBoundaryLines.emplace_back(oldPathCell->GetLines()[2]);

		}
		else
		{
			roop = true;
			oldPathCell = m_AstarResultCells.top(); // 이전 지점을 저장
			m_AstarResultCells.pop(); // A* 셀 한칸 전진
		}


		if (m_AstarResultCells.size() == 0) // 모든 셀을 다 검색했다면 (마지막)
		{

			if (interSection) // 교점이 존재해 한 번에 가지못한 경우 마지막 셀을 넣어줌
			{
				m_OptimalPathPoint.emplace_back(m_endCell->GetCenter());
				m_OptimalPathCell.emplace_back(m_endCell);
			}
			for (auto& boundaryLine : m_AstarBoundaryLines) // 마지막 지점에서 한번에 갈 수 없다면, 마지막 셀도 경로상에 넣어줌
			{
				if (Nalmak_Math::IsIntersectLineToLineOn2D(m_OptimalPathPoint.back(), m_endPos,
					(boundaryLine->GetPoint()[0])->position, (boundaryLine->GetPoint()[1])->position))
				{
					m_OptimalPathPoint.emplace_back(m_endCell->GetCenter());
					m_OptimalPathCell.emplace_back(m_endCell);
					break;
				}
			}
			m_OptimalPathPoint.emplace_back(m_endPos);
			continue;
		}

		currentCell = m_AstarResultCells.top();

		// 셀 안에 라인을 순회
		for (int i = 0; i < 3; ++i)
		{
			NavLine* overlappingLine = nullptr;
			NavLine* line = currentCell->GetLines()[i];

			// 해당 라인이 유효하다면
			if (nullptr != line)
			{
				// 외곽 라인 리스트와 셀 안에 라인과 일치하는지 판단
				for (auto& boundaryLine : m_AstarBoundaryLines)
				{
					if (boundaryLine == line)
						overlappingLine = line;
				}
			}
			// 곂치지 않는다면 외곽 라인 리스트에 추가
			if (nullptr == overlappingLine)
				m_AstarBoundaryLines.emplace_back(line);
			else // 곂친다면 외곽 라인 리스트에서 찾아서 제거
				m_AstarBoundaryLines.erase(remove(m_AstarBoundaryLines.begin(), m_AstarBoundaryLines.end(), overlappingLine), m_AstarBoundaryLines.end());
		}

	}
}

void NavMesh::FindOptimalPath2()
{
	m_OptimalPathPoint2.clear();
	m_OptimalPathPoint2 = m_OptimalPathPoint;
	size_t maxSize = m_OptimalPathPoint.size();
	if (maxSize >= 3)
	{
		for (unsigned int i = 0; i < maxSize - 2; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				Vector3 point = m_OptimalPathCell[i]->GetPoints()[j]->position;
				if (Nalmak_Math::IsExistPointInTriangleInOn2D(point, m_OptimalPathPoint[i], m_OptimalPathPoint[i + 1], m_OptimalPathPoint[i + 2]))
				{
					m_OptimalPathPoint2[i + 1] = point; // 인접하는 삼각형 내부의 점으로 경로를 바꿈
					for (auto& boundaryLine : m_MapBoundaryLines) // 마지막 경로에서 한번에 끝지점까지 갈 수 있나 확인
					{
						if (Nalmak_Math::IsIntersectLineToLineOn2D(m_OptimalPathPoint2[i], m_OptimalPathPoint2[i + 1],
							(boundaryLine->GetPoint()[0])->position, (boundaryLine->GetPoint()[1])->position))
						{
							m_OptimalPathPoint2[i + 1] = m_OptimalPathPoint[i + 1]; // 갈 수 없다면 무게중심으로 다시 되돌림
							break;
						}

					}

					break;
				}

			}

		}

	}
}



void NavMesh::AddCell(NavPoint * _p0, NavPoint * _p1, NavPoint * _p2)
{
	NavCell* cell = new NavCell(this);
	NavPoint* point0 = nullptr;
	NavPoint* point1 = nullptr;
	NavPoint* point2 = nullptr;
	NavLine* line0 = nullptr;
	NavLine* line1 = nullptr;
	NavLine* line2 = nullptr;

	// 이미 존재하는 점일 경우 새로 생성하지 않음
	for (auto& point : m_PointList)
	{
		if (point == _p0)
			point0 = _p0;
		if (point == _p1)
			point1 = _p1;
		if (point == _p2)
			point2 = _p2;
	}


	int NewlineCount = 0;
	// 이미 존재하는 라인일 경우 새로 생성하지 않음
	for (auto& line : m_LineList)
	{
		if (line->GetPoint()[0] == point0 || line->GetPoint()[0] == point1 || line->GetPoint()[0] == point2)
		{
			if (line->GetPoint()[1] == point0 || line->GetPoint()[1] == point1 || line->GetPoint()[1] == point2)
			{
				if (NewlineCount == 0)
					line0 = line;
				if (NewlineCount == 1)
					line1 = line;
				if (NewlineCount == 2)
					line2 = line;
				++NewlineCount;
			}
		}
	}
	// 두 점은 이미 존재하고 한 점이 추가된 경우
	if (point0 == nullptr)
	{
		point0 = _p0;
		line1 = new NavLine(point0, point1);
		line2 = new NavLine(point0, point2);
		m_LineList.emplace_back(line1);
		m_LineList.emplace_back(line2);
		EmplacePoint(point0);
	}
	else if (point1 == nullptr)
	{
		point1 = _p1;
		line1 = new NavLine(point1, point2);
		line2 = new NavLine(point1, point0);
		m_LineList.emplace_back(line1);
		m_LineList.emplace_back(line2);
		EmplacePoint(point1);
	}
	else if (point2 == nullptr)
	{
		point2 = _p2;
		line1 = new NavLine(point2, point0);
		line2 = new NavLine(point2, point1);
		m_LineList.emplace_back(line1);
		m_LineList.emplace_back(line2);

		EmplacePoint(point2);
	}
	else // 세 점이 이미 포함이 되어있는 경우 
	{
		if (nullptr == line0)
		{
			line0 = new NavLine(point0, point1);
			line1 = new NavLine(point1, point2);
			line2 = new NavLine(point2, point0);

			m_LineList.emplace_back(line0);
			m_LineList.emplace_back(line1);
			m_LineList.emplace_back(line2);
		}
		else if (nullptr == line1) // 라인이 이미 한 개가 포함되어있는 경우
		{
			if (point0 != line0->GetPoint()[0] && point0 != line0->GetPoint()[1])
			{
				line1 = new NavLine(line0->GetPoint()[0], point0);
				line2 = new NavLine(line0->GetPoint()[1], point0);
			}
			else if (point1 != line0->GetPoint()[0] && point1 != line0->GetPoint()[1])
			{
				line1 = new NavLine(line0->GetPoint()[0], point1);
				line2 = new NavLine(line0->GetPoint()[1], point1);
			}
			else if (point2 != line0->GetPoint()[0] && point2 != line0->GetPoint()[1])
			{
				line1 = new NavLine(line0->GetPoint()[0], point2);
				line2 = new NavLine(line0->GetPoint()[1], point2);
			}

			m_LineList.emplace_back(line1);
			m_LineList.emplace_back(line2);
		}
		else if (nullptr == line2)// 라인이 이미 두 개가 포함되어있는 경우
		{
			int p0Count = 0;
			int p1Count = 0;
			int p2Count = 0;

			if (line0->GetPoint()[0] == point0)
				++p0Count;
			else if (line0->GetPoint()[0] == point1)
				++p1Count;
			else if (line0->GetPoint()[0] == point2)
				++p2Count;

			if (line1->GetPoint()[0] == point0)
				++p0Count;
			else if (line1->GetPoint()[0] == point1)
				++p1Count;
			else if (line1->GetPoint()[0] == point2)
				++p2Count;

			if (line0->GetPoint()[1] == point0)
				++p0Count;
			else if (line0->GetPoint()[1] == point1)
				++p1Count;
			else if (line0->GetPoint()[1] == point2)
				++p2Count;

			if (line1->GetPoint()[1] == point0)
				++p0Count;
			else if (line1->GetPoint()[1] == point1)
				++p1Count;
			else if (line1->GetPoint()[1] == point2)
				++p2Count;

			if (p0Count == 2)
				line2 = new NavLine(point1, point2);
			else if (p1Count == 2)
				line2 = new NavLine(point0, point2);
			else if (p2Count == 2)
				line2 = new NavLine(point0, point1);

			m_LineList.emplace_back(line2);
		}
		else // 라인이 이미 세 개가 포함되어있는 경우
		{
			Vector3 center = { 0,0,0 };
			center += point0->position;
			center += point1->position;
			center += point2->position;

			center = center / 3;

			for (auto& cell : m_CellList)
			{
				if (cell->GetCenter() == center)
				{
					return;
				}
			}
		}
	}
	// 새로운 셀 등록
	cell->Initialize(point0, point1, point2, line0, line1, line2);

	m_CellList.emplace_back(cell);
}

void NavMesh::EmplacePoint(NavPoint * _point)
{
	m_PointList.emplace_back(_point);


}

void NavMesh::DeleteCell(NavCell * _cell)
{
	NavCell* cell = _cell;

	NavLine* line0 = cell->GetLines()[0];
	NavLine* line1 = cell->GetLines()[1];
	NavLine* line2 = cell->GetLines()[2];
	for (int i = 0; i < 3; ++i)
	{
		_cell->GetPoints()[i]->DeleteParentCell(cell);
		_cell->GetLines()[i]->DeleteParentCell(cell);
	}

	m_CellList.erase(remove(m_CellList.begin(), m_CellList.end(), _cell), m_CellList.end());
	delete _cell;
	_cell = nullptr;
}

void NavMesh::DeleteLine(NavLine * _line)
{
	NavLine* line = _line;
	m_LineList.erase(remove(m_LineList.begin(), m_LineList.end(), line), m_LineList.end());
	delete(line);
	line = nullptr;
}

void NavMesh::DeletePoint(NavPoint * _point)
{
	NavPoint* point = _point;
	m_PointList.erase(remove(m_PointList.begin(), m_PointList.end(), point), m_PointList.end());
	delete(point);
	point = nullptr;
}

void NavMesh::GetAstarPathFromLastCell(NavCell * _cell)
{
	m_AstarResultCells.push(_cell);

	if (nullptr != _cell->GetParent())
		GetAstarPathFromLastCell(_cell->GetParent());
}

void NavMesh::Reset()
{
	m_startCell = nullptr;
	m_endCell = nullptr;
	m_AstarBoundaryLines.clear();
	m_OptimalPathPoint.clear();
	m_OptimalPathCell.clear();
	m_OptimalPathPoint2.clear();
}

void NavMesh::SetData(vector<NavCell*> _cell, vector<NavLine*> _line, vector<NavPoint*> _point)
{
	m_CellList = _cell;
	m_LineList = _line;
	m_PointList = _point;
}

void NavMesh::UpdateMapBoundaryLine()
{
	m_MapBoundaryLines.clear();
	for (auto& line : m_LineList)
	{
		if (nullptr == line->GetParentCell()[0] || nullptr == line->GetParentCell()[1])
			m_MapBoundaryLines.emplace_back(line);
	}
}

void NavMesh::SetStartPosition(const Vector3 & _pos)
{
	m_startPos = _pos;
}

void NavMesh::SetEndPosition(const Vector3 & _pos)
{
	m_endPos = _pos;
}

void NavMesh::CreateFirstPoint(Vector3 _pos)
{
	NavPoint* point0 = new NavPoint(_pos.x, _pos.y, _pos.z);
	EmplacePoint(point0);

}

void NavMesh::CreateSecondPoint(Vector3 _pos)
{
	NavPoint* point1 = new NavPoint(_pos.x, _pos.y, _pos.z);
	EmplacePoint(point1);
}

void NavMesh::CreateThirdPoint(Vector3 _pos)
{
	NavPoint* point0 = m_PointList[0];
	NavPoint* point1 = m_PointList[1];
	NavPoint* point2 = new NavPoint(_pos.x, _pos.y, _pos.z);
	EmplacePoint(point2);

	NavLine* line0 = new NavLine(point0, point1);
	NavLine* line1 = new NavLine(point1, point2);
	NavLine* line2 = new NavLine(point2, point0);
	m_LineList.emplace_back(line0);
	m_LineList.emplace_back(line1);
	m_LineList.emplace_back(line2);


	NavCell* firstCell = new NavCell(this);

	firstCell->Initialize(point0, point1, point2, line0, line1, line2);
	m_CellList.emplace_back(firstCell);
}



void NavMesh::Release()
{
	for (auto& cell : m_CellList)
	{
		SAFE_DELETE(cell);
	}
	for (auto& line : m_LineList)
	{
		SAFE_DELETE(line);
	}
	for (auto& point : m_PointList)
	{
		SAFE_DELETE(point);
	}
	m_CellList.clear();
	m_LineList.clear();
	m_PointList.clear();

	m_openList.clear();
	while (!m_AstarResultCells.empty())
	{
		m_AstarResultCells.pop();
	}
	m_AstarBoundaryLines.clear();
	m_MapBoundaryLines.clear();
	m_OptimalPathCell.clear();
	m_OptimalPathPoint.clear();
	m_OptimalPathPoint2.clear();
}
