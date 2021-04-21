#pragma once
#include "Component.h"

class NavCell;
class NavPoint;
class NavLine;
class NALMAK_DLL NavMesh :
	public Component
{
public:
	struct Desc
	{

	};
public:
	NavMesh(Desc* _desc);
	~NavMesh() = default;
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	//void AddBoudaryLine();
public:
	void AddCell(NavPoint* _p0, NavPoint* _p1, NavPoint* _p2);
private:
	void EmplacePoint(NavPoint* _point);
public:
	vector<NavCell*> GetCellList() const { return m_CellList; }
	vector<NavLine*> GetLineList() const { return m_LineList; }
	vector<NavPoint*> GetPointList() const { return m_PointList; }
	void DeleteCell(NavCell* _cell);
	void DeleteLine(NavLine* _line);
	void DeletePoint(NavPoint* _point);
private:
	vector<NavCell*> m_CellList;
	vector<NavLine*> m_LineList;
	vector<NavPoint*> m_PointList;
public:
	void SetData(vector<NavCell*> _cell, vector<NavLine*> _line, vector<NavPoint*> _point);
public:
	void CreateFirstPoint(Vector3 _pos);
	void CreateSecondPoint(Vector3 _pos);
	void CreateThirdPoint(Vector3 _pos);

};

