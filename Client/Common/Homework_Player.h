#pragma once
#include "Component.h"
class Homework_Player :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Homework_Player(Desc* _desc);
	~Homework_Player();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
public:
	float m_yAxisAngle;

};

