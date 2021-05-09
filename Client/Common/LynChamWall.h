#pragma once
#include "LynState.h"
class LynChamWall :
	public LynState
{
public:
	LynChamWall();
	~LynChamWall();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

