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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

