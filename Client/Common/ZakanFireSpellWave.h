#pragma once
#include "EnemyState.h"
class ZakanFireSpellWave :
	public EnemyState
{
public:
	ZakanFireSpellWave();
	~ZakanFireSpellWave();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

