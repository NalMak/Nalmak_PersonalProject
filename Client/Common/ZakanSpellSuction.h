#pragma once
#include "EnemyState.h"
class ZakanSpellSuction :
	public EnemyState
{
public:
	ZakanSpellSuction();
	~ZakanSpellSuction();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

