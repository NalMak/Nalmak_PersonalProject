#pragma once
#include "LynState.h"
class LynExcape :
	public LynState
{
public:
	LynExcape();
	~LynExcape();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

