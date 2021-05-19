#pragma once
#include "LynState.h"
class LynThunderSlash :
	public LynState
{
public:
	LynThunderSlash();
	~LynThunderSlash();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_targetPosition;
	Vector3 m_startPosition;
	Vector3 m_direction;
	float m_targetDistance;

	float m_speed;
};

