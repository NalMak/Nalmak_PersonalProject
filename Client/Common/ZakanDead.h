#pragma once
#include "EnemyState.h"
class ZakanDead :
	public EnemyState
{
public:
	ZakanDead();
	~ZakanDead();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

