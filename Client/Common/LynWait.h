#pragma once
#include "LynState.h"
class LynWait :
	public LynState
{
public:
	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_sKeyTimer;
};

