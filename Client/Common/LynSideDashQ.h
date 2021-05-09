#pragma once
#include "LynState.h"
class LynSideDashQ :
	public LynState
{
public:
	LynSideDashQ();
	~LynSideDashQ();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_targetPos1;
	Vector3 m_targetPos2;
};

