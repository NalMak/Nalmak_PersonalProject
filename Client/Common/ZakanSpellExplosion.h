#pragma once
#include "EnemyState.h"
// 천공파열
class ZakanSpellExplosion :
	public EnemyState
{
public:
	ZakanSpellExplosion();
	~ZakanSpellExplosion();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

