#pragma once
#include "LynState.h"
class LynVerticalCut_L0 :
	public LynState
{
public:
	LynVerticalCut_L0();
	~LynVerticalCut_L0();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

