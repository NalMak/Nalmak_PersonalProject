#pragma once
#include "EnemyState.h"
class ZakanTeleportCenter :
	public EnemyState
{
public:
	ZakanTeleportCenter();
	~ZakanTeleportCenter();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_landingTarget;
	Vector3 m_jumpPos;
	Vector3 m_flyVelocity;
	float m_flyLength;
	float m_flyTime;
};

