#pragma once
#include "Component.h"
class ZakanFloorAttack :
	public Component
{
public:
	struct Desc
	{

	};
public:
	ZakanFloorAttack(Desc* desc);
	~ZakanFloorAttack();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_explosionTimer;
};

