#pragma once
#include "EnemyState.h"
class ZakanMove :
	public EnemyState
{
public:
	ZakanMove();
	~ZakanMove();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

