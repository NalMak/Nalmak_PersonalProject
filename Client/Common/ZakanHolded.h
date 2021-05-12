#pragma once
#include "EnemyState.h"
class ZakanHolded :
	public EnemyState
{
public:
	ZakanHolded();
	~ZakanHolded();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

