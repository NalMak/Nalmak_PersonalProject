#pragma once
#include "LynState.h"
class LynLand :
	public LynState
{
public:
	LynLand();
	~LynLand();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
