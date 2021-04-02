#pragma once
#include "NavCell.h"
#include "NavPoint.h"
#include "NavLine.h"

class MapTool_NavMeshState :
	public IState
{
public:
	enum NAVMESH_TOOL_MODE
	{
		NAVMESH_TOOL_MODE_INSTALL,
		NAVMESH_TOOL_MODE_SET_START_POINT,
		NAVMESH_TOOL_MODE_SET_END_POINT,
		NAVMESH_TOOL_MODE_MAX
	};
public:
	MapTool_NavMeshState();
	~MapTool_NavMeshState();
private:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	const float m_navPointRadius = 0.1f;
	NavMesh* m_navMesh = nullptr;

	
	NavPoint* m_currentSelectMovePoint;
	NavPoint* m_currentSelectAddPoints[2] = { nullptr, };
	NavCell* m_currentSelectCell = nullptr;

	GameObject* m_startPoint;
	GameObject* m_endPoint;

private:
	bool IsPickingSuccessNavPoint(Vector3 _point);
	GameObject* m_pickingPointsForDebug[2];
	NAVMESH_TOOL_MODE m_toolMode = NAVMESH_TOOL_MODE_INSTALL;
public:
	void SetNavMeshToolMode(NAVMESH_TOOL_MODE _mode);
};

