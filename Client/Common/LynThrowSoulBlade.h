#pragma once
#include "LynState.h"
class LynThrowSoulBlade :
	public LynState
{
public:
	LynThrowSoulBlade();
	~LynThrowSoulBlade();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

