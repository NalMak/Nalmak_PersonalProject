#include "NavCell.h"
#include "NavPoint.h"
#include "NavMesh.h"
#include "NavLine.h"

NavCell::NavCell(NavMesh * _nav)
{
	assert(L"Is not valid navMesh! " && _nav);
	
	m_navMesh = _nav;
}

NavCell::NavCell()
{
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
	}
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
	}
}

void NavCell::Update()
{
	UpdateCenter();
}

void NavCell::AddLine(NavLine * _nav)
{
	if (m_lines[0] && m_lines[1] && m_lines[2])
		return;

	if (!m_lines[0])
		m_lines[0] = _nav;
	if (!m_lines[1])
		m_lines[1] = _nav;
	if (!m_lines[2])
		m_lines[2] = _nav;

}

void NavCell::ReverseCCW()
{
	Vector3 a1 = m_points[0]->position;
	Vector3 a2 = m_points[1]->position;
	Vector3 a3 = m_points[2]->position;

	Vector3 normal = Nalmak_Math::Cross(a1 - a2, a1 - a3);
	normal = Nalmak_Math::Normalize(normal);

	NavPoint* temp = m_points[0];
	m_points[0] = m_points[1];
	m_points[1] = temp;
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




