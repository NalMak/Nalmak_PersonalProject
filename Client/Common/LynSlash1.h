#pragma once
#include "LynState.h"
class LynSlash1 :
	public LynState
{
public:
	LynSlash1();
	~LynSlash1();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	bool m_isCombo;
};

