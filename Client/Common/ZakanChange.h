#pragma once
#include "EnemyState.h"
class ZakanChange :
	public EnemyState
{
public:
	ZakanChange();
	~ZakanChange();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Material* m_bodyMaterial;
	Material* m_armMaterial;
	float m_emissioinPower;
};

