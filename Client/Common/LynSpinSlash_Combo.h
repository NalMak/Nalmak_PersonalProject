#pragma once
#include "LynState.h"
class LynSpinSlash_Combo :
	public LynState
{
public:
	LynSpinSlash_Combo();
	~LynSpinSlash_Combo();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

