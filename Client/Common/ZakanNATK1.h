#pragma once
#include "EnemyState.h"
class ZakanNATK1 :
	public EnemyState
{
public:
	ZakanNATK1();
	~ZakanNATK1();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	void CreateAttackArea();
};

