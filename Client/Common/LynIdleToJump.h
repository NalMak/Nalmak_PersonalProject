#pragma once
#include "LynState.h"
class LynIdleToJump :
	public LynState
{
public:
	LynIdleToJump();
	~LynIdleToJump();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

