#pragma once
#include "LynState.h"
class LynVerticalCut_R1 :
	public LynState
{
public:
	LynVerticalCut_R1();
	~LynVerticalCut_R1();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

