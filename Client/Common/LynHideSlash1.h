#pragma once
#include "LynState.h"
class LynHideSlash1 :
	public LynState
{
public:
	LynHideSlash1();
	~LynHideSlash1();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

