#pragma once
#include "EnemyState.h"
class ZakanMove :
	public EnemyState
{
public:
	ZakanMove();
	~ZakanMove();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

