#pragma once
#include "LynState.h"
class LynBaldo :
	public LynState
{
public:
	LynBaldo();
	~LynBaldo();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
};

