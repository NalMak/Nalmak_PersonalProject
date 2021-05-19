#pragma once
#include "EnemyState.h"
class ZakanChange :
	public EnemyState
{
public:
	ZakanChange();
	~ZakanChange();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Material* m_bodyMaterial;
	Material* m_armMaterial;
	float m_emissioinPower;
};

