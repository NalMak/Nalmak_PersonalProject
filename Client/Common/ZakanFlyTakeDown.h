#pragma once
#include "EnemyState.h"
class ZakanFlyTakeDown :
	public EnemyState
{
public:
	ZakanFlyTakeDown();
	~ZakanFlyTakeDown();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

