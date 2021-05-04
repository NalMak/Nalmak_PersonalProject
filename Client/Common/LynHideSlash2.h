#pragma once
#include "LynState.h"
class LynHideSlash2 :
	public LynState
{
public:
	LynHideSlash2();
	~LynHideSlash2();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

