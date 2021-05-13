#pragma once
#include "Component.h"
class LynWeapon :
	public Component
{
public:
	enum LYN_WEAPON_THROW_STATE
	{
		LYN_WEAPON_THROW_STATE_NONE,
		LYN_WEAPON_THROW_STATE_THROW,
		LYN_WEAPON_THROW_STATE_RETURN,
		LYN_WEAPON_THROW_STATE_MAX
	};
public:
	struct Desc
	{
	};
public:
	LynWeapon(Desc* _desc);
	~LynWeapon();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collision& _col) override;
public:
	void ChaseTarget(Vector3 _targetPos);
	void CreateAttackInfo();
private:
	LYN_WEAPON_THROW_STATE m_weaponState;
public:
	LYN_WEAPON_THROW_STATE GetWeaponState();
};

