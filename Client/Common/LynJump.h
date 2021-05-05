#pragma once
#include "LynState.h"
class LynJump :
	public LynState
{
public:
	LynJump();
	~LynJump();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	int m_jumpDir;
};

