#pragma once
#include "LynState.h"
class LynLightningSlash :
	public LynState
{
public:
	LynLightningSlash();
	~LynLightningSlash();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

