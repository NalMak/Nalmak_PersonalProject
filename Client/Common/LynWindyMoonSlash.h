#pragma once
#include "LynState.h"
class LynWindyMoonSlash :
	public LynState
{
public:
	LynWindyMoonSlash();
	~LynWindyMoonSlash();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

