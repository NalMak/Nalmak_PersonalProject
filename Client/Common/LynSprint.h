#pragma once
#include "LynState.h"
class LynSprint :
	public LynState
{
public:
	LynSprint();
	~LynSprint();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

