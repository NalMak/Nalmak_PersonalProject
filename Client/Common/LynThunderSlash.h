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
	float m_distanceToTarget;
	double m_animPlayTime;
	Vector3 m_toTargetDirection;
};

