#pragma once
#include "LynState.h"
class LynSpinSlash_End :
	public LynState
{
public:
	LynSpinSlash_End();
	~LynSpinSlash_End();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

