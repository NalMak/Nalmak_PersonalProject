#pragma once
#include "LynState.h"
#include "BnS_Enemy.h"
class LynStarAttack :
	public LynState
{
public:
	LynStarAttack();
	~LynStarAttack();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	AttackInfo::Desc m_attackInfo;
	BnS_Enemy* m_target;
};

