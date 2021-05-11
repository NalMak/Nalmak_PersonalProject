#pragma once
#include "StateControl.h"
#include "BnS_Enemy.h"

class EnemyStateControl :
	public StateControl
{
public:
	struct Desc
	{

	};
public:
	EnemyStateControl(Desc* _desc);
	~EnemyStateControl();
private:
	virtual void Initialize() override;
	virtual void Update() override;
private:
	AnimationController* m_animController;
	CharacterController* m_character;
	BnS_Enemy* m_info;
};

