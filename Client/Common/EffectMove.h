#pragma once
#include "Component.h"
class EffectMove :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
		Vector3 direction = { 0,0,1 };
	};

public:
	EffectMove(Desc* _desc);
	virtual ~EffectMove();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	float m_speed;
	Vector3 m_direction;
};

