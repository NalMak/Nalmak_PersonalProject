#pragma once
#include "LynState.h"
class LynVerticalCut_R0 :
	public LynState
{
public:
	LynVerticalCut_R0();
	~LynVerticalCut_R0();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

