#pragma once
#include "LynState.h"
class LynLightningCombo :
	public LynState
{
public:
	LynLightningCombo();
	~LynLightningCombo();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

