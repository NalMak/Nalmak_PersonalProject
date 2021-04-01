#pragma once

class NavMesh;
class NavPoint;
class NavCell;

class NavLine
{
public:
	explicit NavLine(NavPoint* _p0, NavPoint* _p1);
	~NavLine();
public:
	void Release();
	NavCell** GetParentCell();
	void AddParentCell(NavCell* _parent);
	NavPoint** GetPoint() { return m_points; }
	void DeleteParentCell(NavCell* _parent);
private:
	NavPoint* m_points[2];
	NavCell* m_parentCell[2] = { nullptr, };
};

