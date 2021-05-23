#pragma once
#include "LynState.h"
class LynCrash :
	public LynState
{
public:
	LynCrash();
	~LynCrash();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

