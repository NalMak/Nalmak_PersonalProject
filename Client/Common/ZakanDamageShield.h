#pragma once
#include "EnemyState.h"
class ZakanDamageShield :
	public EnemyState
{
public:
	ZakanDamageShield();
	~ZakanDamageShield();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

