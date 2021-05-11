#pragma once
#include "EnemyState.h"
class ZakanSpawn :
	public EnemyState
{
public:
	ZakanSpawn();
	~ZakanSpawn();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

