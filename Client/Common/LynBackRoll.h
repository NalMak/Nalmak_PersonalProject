#pragma once
#include "LynState.h"
class LynBackRoll :
	public LynState
{
public:
	LynBackRoll();
	~LynBackRoll();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

