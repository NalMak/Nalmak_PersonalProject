#pragma once
#include "LynState.h"
class LynGrogy :
	public LynState
{
public:
	LynGrogy();
	~LynGrogy();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

