#pragma once
#include "EnemyState.h"
class ZakanRise :
	public EnemyState
{
public:
	ZakanRise();
	~ZakanRise();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

