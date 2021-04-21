#pragma once

#include "Nalmak_Include.h"

class NavMesh;
class NavPoint;
class NavLine;

class NALMAK_DLL NavCell
{
public:
	explicit NavCell(NavMesh* _nav);
	NavCell();
	~NavCell();
private:
	int num = 0;
public:
	void Release();
	void Initialize(NavPoint * _p0, NavPoint * _p1, NavPoint * _p2, NavLine * _l0, NavLine * _l1, NavLine * _l2);
	void Update();
	void AddLine(NavLine* _nav);
	Vector3 GetCenter()const { return m_centerOfGravityPos; }
	NavLine** GetLines() { return m_lines; }
	NavPoint** GetPoints() { return m_points; }
	NavMesh* GetNavMesh() { return m_navMesh; }
private:
	void UpdateCenter();
private:
	Vector3 m_centerOfGravityPos; // 무게중심점
	NavPoint* m_points[3] = { nullptr, };
	NavLine* m_lines[3] = { nullptr, };
private:
	NavMesh* m_navMesh;
};

