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
public:
	enum LYN_MOVE_DIR_STATE
	{
		LYN_MOVE_DIR_STATE_FRONT,
		LYN_MOVE_DIR_STATE_RIGHT,
		LYN_MOVE_DIR_STATE_FRONTRIGHT,
		LYN_MOVE_DIR_STATE_LEFT,
		LYN_MOVE_DIR_STATE_FRONTLEFT,
		LYN_MOVE_DIR_STATE_BACK,
		LYN_MOVE_DIR_STATE_BACKRIGHT,
		LYN_MOVE_DIR_STATE_BACKLEFT,
		LYN_MOVE_DIR_STATE_NONE,
		LYN_MOVE_DIR_STATE_MAX
	};
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
	LynStateControl* m_lynControl;
private:

};

