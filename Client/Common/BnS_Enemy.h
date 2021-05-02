#pragma once
#include "Component.h"
class BnS_Enemy :
	public Component
{
public:
	struct Desc
	{
		UINT hp = 100000;
		float hitRadius = 3.f;
		UINT power = 1500;
		float detectionRadius = 10.f;
	};
public:
	BnS_Enemy(Desc* _desc);
	~BnS_Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	void OnTriggerEnter(Collisions& _col) override;
	void OnTriggerExit(Collisions& _col) override;
private:
	UINT m_hp;
	UINT m_power;
	float m_hitRadius;
	BATTLE_STATE m_battleState;
	bool m_isAggro;
	float m_detectionRadius;
	GameObject* m_target;
	CharacterController* m_controller;
};

