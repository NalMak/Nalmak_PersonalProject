#pragma once
#include "LynState.h"
class LynTurning :
	public LynState
{
public:
	LynTurning();
	~LynTurning();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

