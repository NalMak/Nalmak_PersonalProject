#pragma once
#include "LynState.h"
class LynBackStep :
	public LynState
{
public:
	LynBackStep();
	~LynBackStep();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

