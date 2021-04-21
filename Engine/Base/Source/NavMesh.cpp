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



void NavMesh::SetData(vector<NavCell*> _cell, vector<NavLine*> _line, vector<NavPoint*> _point)
{
	m_CellList = _cell;
	m_LineList = _line;
	m_PointList = _point;
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

}
