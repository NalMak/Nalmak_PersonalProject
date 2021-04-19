#pragma once
#include "Component.h"
class Player :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Player(Desc* _desc);
	~Player();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

