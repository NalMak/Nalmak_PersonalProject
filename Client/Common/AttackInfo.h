#pragma once
#include "Component.h"
class AttackInfo :
	public Component
{
public:
	struct Desc
	{
		GameObject* host = nullptr;

		ATTACK_TYPE attackType = ATTACK_TYPE_DEFAULT;
		COLLIDER_TYPE colliderType = COLLIDER_TYPE_BOX;
		UINT power = 100;
		bool isCritical = false;

		float width = 2;
		float height = 4;
		float depth = 8;
		float radius = 2;
	};
public:
	AttackInfo(Desc* _desc);
	~AttackInfo();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	ATTACK_TYPE m_attackType;
	UINT m_power;
	bool m_isCritical;

	float m_width;
	float m_height;
	float m_depth;
	float m_radius;

	UINT m_frameLife;
	COLLIDER_TYPE m_colliderType;
};

