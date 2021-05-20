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

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_explosionTimer;
};

