#pragma once
#include "LynState.h"
class LynWindyMoonSlash :
	public LynState
{
public:
	LynWindyMoonSlash();
	~LynWindyMoonSlash();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

