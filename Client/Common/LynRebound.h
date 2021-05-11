#pragma once
#include "LynState.h"
class LynRebound : public LynState
{
public:
	LynRebound();
	~LynRebound();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	bool m_isRight;
};

