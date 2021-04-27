#pragma once
#include "LynState.h"
class LynJumpToIdle :
	public LynState
{
public:
	LynJumpToIdle();
	~LynJumpToIdle();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

};

