#pragma once
#include "LynState.h"
class LynKnockBackMiddle :
	public LynState
{
public:
	LynKnockBackMiddle();
	~LynKnockBackMiddle();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

