#pragma once
#include "LynState.h"
class LynMove :
	public LynState
{
public:
	LynMove();
	~LynMove();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

