#pragma once
#include "LynState.h"
class LynEventIdle :
	public LynState
{
public:
	LynEventIdle();
	~LynEventIdle();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	int m_animIdex;
};

