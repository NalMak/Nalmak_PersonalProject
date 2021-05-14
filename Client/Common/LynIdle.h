#pragma once
#include "LynState.h"
class LynIdle :
	public LynState
{
public:
	LynIdle();
	~LynIdle();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	LYN_STATE m_state;
	
};

