#pragma once
#include "Nalmak_Include.h"

class NavMesh;
class NavCell;
class NavLine;

class NALMAK_DLL NavPoint
{
public:
	explicit NavPoint();
	explicit NavPoint(float _x, float _y, float _z);
	~NavPoint() = default;
public:
	void Release();
public:
	Vector3 position;
private:
	vector<NavCell*> m_parentCells;
public:
	void DeleteParentCell(NavCell* _cell);
	void AddParentCell(NavCell* _cell);
	vector<NavCell*> GetParentCells();
};

