#include "NavLine.h"

#include "NavCell.h"
#include "NavPoint.h"
#include "NavMesh.h"


NavLine::NavLine(NavPoint * _p0, NavPoint * _p1)
{
	m_points[0] = _p0;
	m_points[1] = _p1;
}

NavLine::~NavLine()
{
}

void NavLine::Release()
{
}

NavCell ** NavLine::GetParentCell()
{
	return m_parentCell;
}

void NavLine::AddParentCell(NavCell * _parent)
{
	assert(_parent);

	if (m_parentCell[0] == nullptr)
		m_parentCell[0] = _parent;
	else if (m_parentCell[1] == nullptr)
		m_parentCell[1] = _parent;
}

void NavLine::DeleteParentCell(NavCell * _parent)
{
	assert(_parent);

	NavCell* parent = _parent;
	if (m_parentCell[0] == parent)
		m_parentCell[0] = nullptr;
	else if (m_parentCell[1] == parent)
		m_parentCell[1] = nullptr;

	if (nullptr == m_parentCell[0] && nullptr == m_parentCell[1])
	{
		_parent->GetNavMesh()->DeleteLine(this);
	}
}
