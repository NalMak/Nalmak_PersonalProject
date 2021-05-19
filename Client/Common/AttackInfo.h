#pragma once
#include "Component.h"
class AttackInfo :
	public Component
{
	using HitEvent = function<void(void)>;
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
		float ccTime = 2.f;
		float lifeTime = 0.1f;
		UINT innerPower = 0;
		wstring soundName = L"";
	};
public:
	AttackInfo(Desc* _desc);
	~AttackInfo();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	ATTACK_TYPE m_attackType;
	UINT m_power;
	bool m_isCritical;

	float m_width;
	float m_height;
	float m_depth;
	float m_radius;
	float m_ccTime;
	float m_lifeTime;
	UINT m_innerPower;
	wstring m_soundName;
	HitEvent* m_hitEvent;
public:
	void AddHitEvent(HitEvent _hitEvent);
	GameObject* GetHost();
private:
	GameObject* m_host;
	COLLIDER_TYPE m_colliderType;
};

