#pragma once
#include "EnemyState.h"
class ZakanSpawn :
	public EnemyState
{
public:
	ZakanSpawn();
	~ZakanSpawn();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

