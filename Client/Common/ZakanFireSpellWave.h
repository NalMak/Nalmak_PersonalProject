#pragma once
#include "EnemyState.h"
class ZakanFireSpellWave :
	public EnemyState
{
public:
	ZakanFireSpellWave();
	~ZakanFireSpellWave();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	void CreateFloorAttack();
	void CreateFloorAttack(float _x, float _z);
	int m_patterIndex;
};

