#pragma once
#include "LynState.h"
class LynSlash1 :
	public LynState
{
public:
	LynSlash1();
	~LynSlash1();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	bool m_isCombo;
};

