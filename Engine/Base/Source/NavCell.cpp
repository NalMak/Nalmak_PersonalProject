#include "NavCell.h"
#include "NavPoint.h"
#include "NavMesh.h"
#include "NavLine.h"

NavCell::NavCell(NavMesh * _nav)
{
	assert(L"Is not valid navMesh! " && _nav);
	
	m_navMesh = _nav;
}

NavCell::~NavCell()
{
}

void NavCell::Release()
{
	for (int i = 0; i < 3; ++i)
	{
		m_lines[i] = nullptr;
		m_points[i] = nullptr;
		m_AdjacentCellList[i] = nullptr;
	}
}

void NavCell::Reset()
{
	m_state = CELL_STATE_DEFAULT;
	m_parent = nullptr;
}

void NavCell::Initialize(NavPoint * _p0, NavPoint * _p1, NavPoint * _p2, NavLine * _l0, NavLine * _l1, NavLine * _l2)
{
	m_points[0] = _p0;
	m_points[1] = _p1;
	m_points[2] = _p2;

	m_lines[0] = _l0;
	m_lines[1] = _l1;
	m_lines[2] = _l2;

	for (int i = 0; i < 3; ++i)
	{
		m_lines[i]->AddParentCell(this);
		m_points[i]->AddParentCell(this);
		for (int j = 0; j < 2; ++j)
		{
			if (m_lines[i]->GetParentCell()[j] != nullptr)
				m_lines[i]->GetParentCell()[j]->UpdateAdjacentCellList();
		}
	}
}

void NavCell::Update()
{
	UpdateCenter();
	UpdateCost();
}

void NavCell::UpdateCenter()
{
	float totalX = 0;
	float totalY = 0;
	float totalZ = 0;

	for (int i = 0; i < 3; ++i)
	{
		totalX += m_points[i]->position.x;
		totalY += m_points[i]->position.y;
		totalZ += m_points[i]->position.z;

	}

	m_centerOfGravityPos.x = totalX / 3.f;
	m_centerOfGravityPos.y = totalY / 3.f;
	m_centerOfGravityPos.z = totalZ / 3.f;

}

void NavCell::UpdateAdjacentCellList()
{
}

NavCell * NavCell::GetParent() const
{
	return nullptr;
}

void NavCell::SetParent(NavCell * _parent)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_lines[i]->GetParentCell()[j] != this)
			{
				m_AdjacentCellList[i] = m_lines[i]->GetParentCell()[j];
			}
		}
	}
}

float NavCell::GetCost()
{
	if (nullptr != m_parent)
		g = m_parent->GetCost() + Nalmak_Math::Distance(m_parent->GetCenter(), m_centerOfGravityPos);

	f = g + h;

	return f;
}

void NavCell::UpdateCost()
{
	assert(m_navMesh);

	h = Nalmak_Math::Distance(m_navMesh->GetEndPosition(), m_centerOfGravityPos);
	g = Nalmak_Math::Distance(m_navMesh->GetStartPosition(), m_centerOfGravityPos);
}

void NavCell::SetState(CELL_STATE _state)
{
	m_state = _state;
}

CELL_STATE NavCell::GetState() const
{
	return m_state;
}


