#include "stdafx.h"
#include "LynWeapon.h"


LynWeapon::LynWeapon(Desc * _desc)
{
}

LynWeapon::~LynWeapon()
{
}

void LynWeapon::Initialize()
{
	m_weaponState = LYN_WEAPON_THROW_STATE_NONE;
}

void LynWeapon::Update()
{
}

void LynWeapon::OnTriggerEnter(Collision & _col)
{
	m_weaponState = LYN_WEAPON_THROW_STATE_RETURN;
}

void LynWeapon::ChaseTarget(Vector3 _targetPos)
{
	m_transform->RotateZ(2);
}

void LynWeapon::CreateAttackInfo()
{
	m_weaponState = LYN_WEAPON_THROW_STATE_THROW;
}

LynWeapon::LYN_WEAPON_THROW_STATE LynWeapon::GetWeaponState()
{
	return m_weaponState;
}

