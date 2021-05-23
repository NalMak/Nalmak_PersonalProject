#pragma once
#include "LynState.h"
class LynSprint :
	public LynState
{
public:
	LynSprint();
	~LynSprint();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

