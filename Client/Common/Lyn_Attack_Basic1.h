#pragma once
#include "LynState.h"
class Lyn_Attack_Basic1 :
	public LynState
{
public:
	Lyn_Attack_Basic1();
	~Lyn_Attack_Basic1();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

