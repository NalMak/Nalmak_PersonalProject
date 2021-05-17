#pragma once
#include "IState.h"
#include "EnemyStateControl.h"
#include "BnS_Enemy.h"
#include "AttackInfo.h"
#include "CameraShake.h"
#include "BnS_MainCamera.h"

class EnemyState :
	public IState
{
	friend class EnemyStateControl;
public:
	EnemyState();
	~EnemyState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
protected:
	AnimationController* m_animController;
	BnS_Enemy* m_info;
	CharacterController* m_character;
	BnS_MainCamera* m_bnsMainCam;
	AudioSource* m_audio;
};

