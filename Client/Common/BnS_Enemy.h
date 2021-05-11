#pragma once
#include "Component.h"
#include "AttackInfo.h"

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
		Vector4 volumeRect = { 5,10,5,0};
	};
public:
	BnS_Enemy(Desc* _desc);
	~BnS_Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;

public:
	const Vector4& GetVolume();
	GameObject* GetTarget();
	void LostTarget();
private:
	Vector4 m_volumeRect;
	UINT m_hp;
	UINT m_power;
	float m_hitRadius;
	BATTLE_STATE m_battleState;
	bool m_isAggro;
	float m_detectionRadius;
	GameObject* m_target;
	CharacterController* m_character;
};

