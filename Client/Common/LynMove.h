#pragma once
#include "Component.h"
class LynInfo;

class LynMove :
	public Component
{
	enum LYN_MOVE_STATE
	{
		LYN_MOVE_STATE_IDLE,
		LYN_MOVE_STATE_RUN,
		LYN_MOVE_STATE_JUMP,
		LYN_MOVE_STATE_MAX
	};
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
		LYN_MOVE_DIR_STATE_LEFTTORIGHT,
		LYN_MOVE_DIR_STATE_RIGHTTOLEFT,
		LYN_MOVE_DIR_STATE_NONE,
		LYN_MOVE_DIR_STATE_MAX
	};
public:
	struct Desc
	{

	};
public:
	LynMove(Desc* _desc);
	~LynMove();
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	Vector3 m_inputDir;
	Vector3 m_targetInput;
	LynInfo* m_info;
	LYN_MOVE_DIR_STATE m_moveDirState;
	LYN_MOVE_STATE m_moveState;
	CharacterController* m_charcterController;
	AnimationController* m_animController;
	Vector3 m_directionState[10] = {
							{ 0, 0, 1 },
							{ 1,0,0 },
							Nalmak_Math::Normalize({ 1,0,1 }),
							{ -1,0,0 },
							Nalmak_Math::Normalize({ -1,0,1 }),
							{ 0,0,-1 },
							Nalmak_Math::Normalize({ 1,0,-1 }),
							Nalmak_Math::Normalize({ -1,0,-1 }),
							{ -0.6f,0,0 },
							{ 0.6f,0,0 }
	};
private:
	void UpdateMoveState();
	void UpdateDirectionByKey();

	
};

