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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	GameObject* m_target;
};

