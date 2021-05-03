#pragma once
#include "IState.h"
#include "LynInfo.h"
#include "AttackInfo.h"
#include "LynStateControl.h"

class LynState :
	public IState
{
	friend class LynStateControl;
public:
	LynState();
	~LynState();	
protected:
	// IState을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
protected:
	AnimationController* m_animController_lower;
	AnimationController* m_animController_upper;

	CharacterController* m_character;
	LynInfo* m_info;
	LynStateControl* m_lynMoveControl;
	LynStateControl* m_lynSkillControl;

private:

};

