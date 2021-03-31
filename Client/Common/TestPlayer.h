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
private:
	RigidBody* m_rigidBody = nullptr;
};

