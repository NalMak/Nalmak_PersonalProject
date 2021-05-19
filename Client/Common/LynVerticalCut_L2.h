#pragma once
#include "LynState.h"
class LynVerticalCut_L2 :
	public LynState
{
public:
	LynVerticalCut_L2();
	~LynVerticalCut_L2();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
};

