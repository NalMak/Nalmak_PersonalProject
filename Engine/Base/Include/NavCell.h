#pragma once

#include "Nalmak_Include.h"

class NavMesh;
class NavPoint;
class NavLine;

class NavCell
{
public:
	explicit NavCell(NavMesh* _nav);
	~NavCell();
private:
	int num = 0;
public:
	void Release();
	void Reset();
	void Initialize(NavPoint * _p0, NavPoint * _p1, NavPoint * _p2, NavLine * _l0, NavLine * _l1, NavLine * _l2);
	void Update();
	Vector3 GetCenter()const { return m_centerOfGravityPos; }
	NavCell** GetAdjacentCells() { return m_AdjacentCellList; }
	NavLine** GetLines() { return m_lines; }
	NavPoint** GetPoints() { return m_points; }
	NavMesh* GetNavMesh() { return m_navMesh; }
private:
	void UpdateCenter();
	void UpdateAdjacentCellList();
private:
	Vector3 m_centerOfGravityPos; // 무게중심점
	NavPoint* m_points[3] = { nullptr, };
	NavLine* m_lines[3] = { nullptr, };
	NavCell* m_AdjacentCellList[3] = { nullptr, };
private:
	NavMesh* m_navMesh;





	//////////////////////////////////
	// for A*
private:
	NavCell* m_parent = nullptr;
public:
	NavCell* GetParent()const;
	void SetParent(NavCell* _parent);
public:
	float f = 0; // 최종 값
	float h = 0; // 목적지까지의 거리
	float g = 0; // 이동거리
public:
	float GetCost();
private:
	void UpdateCost();
	CELL_STATE m_state = CELL_STATE_DEFAULT;
public:
	void SetState(CELL_STATE _state);
	CELL_STATE GetState()const;
	//
	//////////////////////////////////

	//https://jieun0113.tistory.com/111  참고자료 (셀 내부에 점이 있는지 판단)
};

