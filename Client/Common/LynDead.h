#pragma once
#include "LynState.h"
class LynDead :
	public LynState
{
public:
	LynDead();
	~LynDead();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

