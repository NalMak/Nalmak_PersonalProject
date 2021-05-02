#pragma once
#include "LynState.h"
class LynBackStep :
	public LynState
{
public:
	LynBackStep();
	~LynBackStep();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

