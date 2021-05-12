#pragma once
#include "LynState.h"
class LynIlSum :
	public LynState
{
public:
	LynIlSum();
	~LynIlSum();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

