#pragma once
#include "LynState.h"
class LynVerticalCut_L2 :
	public LynState
{
public:
	LynVerticalCut_L2();
	~LynVerticalCut_L2();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
};

