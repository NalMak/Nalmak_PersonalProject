#pragma once

class MapTool_NavMeshState :
	public IState
{
public:
	MapTool_NavMeshState();
	~MapTool_NavMeshState();
private:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

