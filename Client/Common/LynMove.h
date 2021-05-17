#pragma once
#include "LynState.h"
class LynMove :
	public LynState
{
public:
	LynMove();
	~LynMove();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	LYN_MOVE_DIR_STATE m_dirState;
	LYN_STATE m_state;
private:
	void PlayAnimationByDirection();
private:
	float m_soundInterval;
};

