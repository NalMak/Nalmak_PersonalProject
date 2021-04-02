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
public:
	bool FindPath();
private:
	void RecordAstarPath(NavCell* _cell);
	void FindOptimalPath();
	void FindOptimalPath2();
	//void AddBoudaryLine();
public:
	bool FindAstarPath();
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
	vector<GameObject*> m_debugObjects;
public:
	vector<NavCell*> m_openList;
private:
	// for A* 
	Vector3 m_startPos;
	Vector3 m_endPos;
	NavCell* m_startCell = nullptr;
	NavCell* m_endCell = nullptr;
	stack<NavCell*> m_AstarResultCells; // A* �˰������� ���� ���� ����
	vector<NavLine*> m_AstarBoundaryLines; // �ܰ� ���� ����
	vector<NavLine*> m_MapBoundaryLines; // �ܰ� ���� ����

	vector<Vector3> m_OptimalPathPoint; // ����ȭ�� �ִܰŸ� ��
	vector<Vector3> m_OptimalPathPoint2; // ����ȭ�� �ִܰŸ� ��
	vector<NavCell*> m_OptimalPathCell; // ����ȭ�� �ִܰŸ� ��
	void GetAstarPathFromLastCell(NavCell* _cell);
public:
	void Reset();
	vector<Vector3> GetPath() { return m_OptimalPathPoint2; }

	void UpdateMapBoundaryLine();
	NavCell* GetEndCell() { return m_endCell; }
	void SetStartPosition(const Vector3& _pos);
	void SetEndPosition(const Vector3& _pos);
	const Vector3& GetStartPosition() { return m_startPos; }
	const Vector3& GetEndPosition() { return m_endPos; }
public:
	void CreateFirstPoint(Vector3 _pos);
	void CreateSecondPoint(Vector3 _pos);
	void CreateThirdPoint(Vector3 _pos);

};

