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
	m_swordTrail = GetComponent<TrailRenderer>();

	m_trailStartPos = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_trailStartPos->SetParents(m_gameObject);
	m_trailStartPos->SetPosition(0, 10, 0);

	m_trailEndPos = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_trailEndPos->SetParents(m_gameObject);
	m_trailEndPos->SetPosition(0, 35, 0);
	//m_swordTrail->
}

void LynWeapon::Update()
{
}

void LynWeapon::PreRender()
{
	m_swordTrail->RecordTrail(m_trailStartPos->GetTransform()->GetWorldPosition(), m_trailEndPos->GetTransform()->GetWorldPosition());
}

void LynWeapon::OnTriggerEnter(Collision & _col)
{
	m_weaponState = LYN_WEAPON_THROW_STATE_RETURN;
}

void LynWeapon::StartTrail()
{
	m_swordTrail->ResetTrail();
	m_swordTrail->Play();
}

void LynWeapon::EndTrail()
{
	m_swordTrail->ResetTrail();
	m_swordTrail->Stop();
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

