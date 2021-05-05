#pragma once
#include "LynState.h"
class LynSideDashE :
	public LynState
{
public:
	LynSideDashE();
	~LynSideDashE();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_turnTotalTime;
	float m_turnCurrentTime;
	Quaternion m_startRot;
	Quaternion m_endRot;
};

