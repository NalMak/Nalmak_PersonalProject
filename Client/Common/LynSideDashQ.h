#pragma once
#include "LynState.h"
class LynSideDashQ :
	public LynState
{
public:
	LynSideDashQ();
	~LynSideDashQ();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

