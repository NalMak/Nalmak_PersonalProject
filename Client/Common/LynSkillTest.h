#pragma once
#include "LynState.h"
class LynSkillTest :
	public LynState
{
public:
	LynSkillTest();
	~LynSkillTest();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

