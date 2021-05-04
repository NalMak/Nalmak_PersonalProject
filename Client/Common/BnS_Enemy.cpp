#include "stdafx.h"
#include "BnS_Enemy.h"
#include "BnS_DamageFont.h"


BnS_Enemy::BnS_Enemy(Desc * _desc)
{
	m_hp = _desc->hp;
	m_power  = _desc->power;
	m_hitRadius = _desc->hitRadius;
	m_detectionRadius = _desc->detectionRadius; 
	m_battleState = BATTLE_STATE_WEAK;
	m_isAggro = false;
	m_target = nullptr;

	m_volumeRect = _desc->volumeRect;
}

BnS_Enemy::~BnS_Enemy()
{
}

void BnS_Enemy::Initialize()
{
	//m_controller = GetComponent<CharacterController>();
	//m_gameObject->SetLayer(OBJECT_LAYER_ENEMY);
	//m_gameObject->SetTag(OBJECT_TAG_ENEMY);
}

void BnS_Enemy::Update()
{
	DEBUG_LOG(L"enemy hp", m_hp);
}

void BnS_Enemy::OnTriggerEnter(Collision & _col)
{
	if (_col.hitObj->GetTag() == OBJECT_TAG_ATTACKINFO)
	{
		m_hp -= _col.hitObj->GetComponent<AttackInfo>()->m_power;
		

		BnS_DamageFont::Desc damageFont;
		damageFont.damage = Nalmak_Math::Rand(80, 120);
		damageFont.isCritical = Nalmak_Math::Random<bool>(true,true,true,false,false);
		INSTANTIATE()->AddComponent<BnS_DamageFont>(&damageFont)->SetPosition(m_transform->GetWorldPosition() + Vector3(0, 6, 0));
	}
}

void BnS_Enemy::OnTriggerExit(Collision & _col)
{
}

const Vector4 & BnS_Enemy::GetVolume()
{
	return m_volumeRect;	
}
