#pragma once
#include "LynState.h"
class LynDown :
	public LynState
{
public:
	LynDown();
	~LynDown();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

