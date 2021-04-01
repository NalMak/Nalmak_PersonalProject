#include "NavPoint.h"

#include "NavCell.h"
#include "NavLine.h"
#include "NavMesh.h"


NavPoint::NavPoint(float _x, float _y, float _z)
{
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void NavPoint::Release()
{
}

void NavPoint::DeleteParentCell(NavCell * _cell)
{
	assert(L"Is not valid NavCell!" && _cell);

	NavCell* parent = _cell;

	m_parentCells.erase(remove(m_parentCells.begin(), m_parentCells.end(), _cell), m_parentCells.end());

	if (m_parentCells.empty())
	{
		_cell->GetNavMesh()->DeletePoint(this);
	}
}

void NavPoint::AddParentCell(NavCell * _cell)
{
	assert(_cell);

	m_parentCells.emplace_back(_cell);
}

vector<NavCell*> NavPoint::GetParentCells()
{
	return m_parentCells;
}
