#pragma once
#include "EnemyState.h"
class ZakanGrab :
	public EnemyState
{
public:
	ZakanGrab();
	~ZakanGrab();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

