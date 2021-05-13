#pragma once
#include "LynState.h"
class LynWakeUp :
	public LynState
{
public:
	LynWakeUp();
	~LynWakeUp();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

