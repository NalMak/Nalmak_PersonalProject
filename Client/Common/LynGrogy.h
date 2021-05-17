#pragma once
#include "LynState.h"
class LynGrogy :
	public LynState
{
public:
	LynGrogy();
	~LynGrogy();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_ccTime;
	float m_backRollTimer = 1.f;
};

