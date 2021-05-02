#pragma once
#include "LynState.h"
class LynSpinSlash_End :
	public LynState
{
public:
	LynSpinSlash_End();
	~LynSpinSlash_End();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

