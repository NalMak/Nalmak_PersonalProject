#pragma once
#include "LynState.h"
class LynWakeUp :
	public LynState
{
public:
	LynWakeUp();
	~LynWakeUp();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

