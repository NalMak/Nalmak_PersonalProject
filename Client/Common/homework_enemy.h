#pragma once
#include "Component.h"
class homework_enemy :
	public Component
{
public:
	struct Desc
	{
		GameObject* target;
	};
public:
	homework_enemy(Desc* _Desc);
	~homework_enemy();
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	class Homework_Player* m_player;
};

