#pragma once
#include "LynState.h"
class LynHideSlash3 :
	public LynState
{
public:
	LynHideSlash3();
	~LynHideSlash3();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

