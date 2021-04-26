#pragma once
#include "LynState.h"
class LynRun :
	public LynState
{
private:
	enum MOVE_DIRECTION
	{
		MOVE_DIRECTION_UP = 1,
		MOVE_DIRECTION_LEFT = 2,
		MOVE_DIRECTION_RIGHT = 4,
		MOVE_DIRECTION_DOWN = 8,
	};
public:
	LynRun();
	~LynRun();

	// LynState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	UINT m_preDirection;
	UINT m_moveDirection;

private:
	UINT CalcKeyState();
	void UpdateAnimState();
};

