#pragma once
#include "LynState.h"
class LynHideSlash3 :
	public LynState
{
public:
	LynHideSlash3();
	~LynHideSlash3();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

