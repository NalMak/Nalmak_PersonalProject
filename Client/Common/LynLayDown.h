#pragma once
#include "LynState.h"
class LynLayDown :
	public LynState
{
public:
	LynLayDown();
	~LynLayDown();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_downTimer;
	float m_backRollTimer;
};

