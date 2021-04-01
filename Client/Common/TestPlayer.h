#pragma once
#include "Component.h"
class TestPlayer :
	public Component
{
public:
	struct Desc
	{

	};
public:
	TestPlayer(Desc* _desc);
	~TestPlayer();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(Collisions& _col)override;
	virtual void OnCollisionStay(Collisions& _col)override;
	virtual void OnCollisionExit(Collisions& _col)override;

private:
	RigidBody* m_rigidBody = nullptr;
};

