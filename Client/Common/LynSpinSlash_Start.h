#pragma once
#include "LynState.h"
class LynSpinSlash_Start :
	public LynState
{
public:
	LynSpinSlash_Start();
	~LynSpinSlash_Start();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	AttackInfo::Desc m_attack;
	GameObject* m_effect;
};

