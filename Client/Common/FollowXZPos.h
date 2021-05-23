#pragma once
#include "Component.h"
class FollowXZPos :
	public Component
{
public:
	struct Desc
	{
	};
public:
	FollowXZPos(Desc* _desc);
	~FollowXZPos();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	GameObject* m_target;
};

