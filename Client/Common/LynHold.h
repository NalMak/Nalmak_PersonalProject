#pragma once
#include "LynState.h"
class LynHold :
	public LynState
{
public:
	LynHold();
	~LynHold();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

