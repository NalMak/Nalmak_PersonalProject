#pragma once
#include "LynState.h"
class LynKnockBackLong :
	public LynState
{
public:
	LynKnockBackLong();
	~LynKnockBackLong();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

