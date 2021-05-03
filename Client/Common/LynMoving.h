//#pragma once
//#include "Component.h"
//class LynInfo;
//
//class LynMoving :
//	public Component
//{
//	enum LYN_MOVE_STATE
//	{
//		LYN_MOVE_STATE_IDLE,
//		LYN_MOVE_STATE_RUN,
//		LYN_MOVE_STATE_JUMP,
//		LYN_MOVE_STATE_LAND,
//		LYN_MOVE_STATE_MAX
//	};
//	
//public:
//	struct Desc
//	{
//
//	};
//public:
//	LynMoving(Desc* _desc);
//	~LynMoving();
//	// Component을(를) 통해 상속됨
//	virtual void Initialize() override;
//	virtual void Update() override;
//private:
//	Vector3 m_inputDir;
//	Vector3 m_targetInput;
//	LynInfo* m_info;
//	LYN_MOVE_STATE m_moveState;
//	LYN_MOVE_STATE m_preState;
//
//	CharacterController* m_charcterController;
//	AnimationController* m_animController_upper;
//	AnimationController* m_animController_lower;
//
//	Vector3 m_directionState[9] = {
//							{ 0, 0, 1 },
//							{ 1,0,0 },
//							Nalmak_Math::Normalize({ 1,0,1 }),
//							{ -1,0,0 },
//							Nalmak_Math::Normalize({ -1,0,1 }),
//							{ 0,0,-1 },
//							Nalmak_Math::Normalize({ 1,0,-1 }),
//							Nalmak_Math::Normalize({ -1,0,-1 }),
//							{ 0,0,0 }
//	};
//private:
//	void UpdateMoveState();
//	void UpdateDirectionByKey();
//
//	
//};
//
