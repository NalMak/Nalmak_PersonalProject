#pragma once
#include "EnemyState.h"
// õ���Ŀ�
class ZakanSpellExplosion :
	public EnemyState
{
public:
	ZakanSpellExplosion();
	~ZakanSpellExplosion();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

