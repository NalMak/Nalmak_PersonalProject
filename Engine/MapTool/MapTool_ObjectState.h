#pragma once

class MapTool_ObjectState :
	public IState
{
public:
	MapTool_ObjectState();
	~MapTool_ObjectState();
private:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

