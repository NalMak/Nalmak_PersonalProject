#pragma once
#include "IState.h"
#include "LynInfo.h"

class LynState :
	public IState
{
	friend class LynStateControl;
public:
	LynState();
	~LynState();

protected:
	// IState��(��) ���� ��ӵ�
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
protected:
	AnimationController* m_animController;
	CharacterController* m_character;
	LynInfo* m_info;
};
