#pragma once
#include "EnemyState.h"
class ZakanNATK2 :
	public EnemyState
{
public:
	ZakanNATK2();
	~ZakanNATK2();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

