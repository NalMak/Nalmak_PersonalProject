#pragma once
#include "LynState.h"
class LynFrontKick :
	public LynState
{
public:
	LynFrontKick();
	~LynFrontKick();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

