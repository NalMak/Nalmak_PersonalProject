#pragma once
#include "LynState.h"
class LynFall :
	public LynState
{
public:
	LynFall();
	~LynFall();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
