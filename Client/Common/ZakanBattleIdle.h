#pragma once
#include "EnemyState.h"
class ZakanBattleIdle :
	public EnemyState
{
public:
	ZakanBattleIdle();
	~ZakanBattleIdle();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	ZAKAN_PATTERN m_phaseIndex;
};

