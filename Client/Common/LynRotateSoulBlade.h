#pragma once
#include "LynState.h"
class LynRotateSoulBlade :
	public LynState
{
public:
	LynRotateSoulBlade();
	~LynRotateSoulBlade();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

