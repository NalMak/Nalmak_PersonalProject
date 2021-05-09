#pragma once
#include "LynState.h"
class LynLowerSlash2 :
	public LynState
{
public:
	LynLowerSlash2();
	~LynLowerSlash2();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

