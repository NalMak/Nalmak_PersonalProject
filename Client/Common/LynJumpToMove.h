#pragma once
#include "LynState.h"
class LynJumpToMove :
	public LynState
{
public:
	LynJumpToMove();
	~LynJumpToMove();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float m_height;
};

