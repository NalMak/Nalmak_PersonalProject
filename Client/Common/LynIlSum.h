#pragma once
#include "LynState.h"
class LynIlSum :
	public LynState
{
public:
	LynIlSum();
	~LynIlSum();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

