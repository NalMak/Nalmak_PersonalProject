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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void OnTriggerEnter(Collision& _col) override;
public:
	void StartTrail();
	void EndTrail();
public:
	void ChaseTarget(Vector3 _targetPos);
	void CreateAttackInfo();
private:
	LYN_WEAPON_THROW_STATE m_weaponState;
	TrailRenderer* m_swordTrail;
public:
	LYN_WEAPON_THROW_STATE GetWeaponState();

	GameObject* m_trailStartPos;
	GameObject* m_trailEndPos;

};

