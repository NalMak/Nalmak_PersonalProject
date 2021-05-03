#include "stdafx.h"
#include "BnS_Enemy.h"



BnS_Enemy::BnS_Enemy(Desc * _desc)
{
	m_hp = _desc->hp;
	m_power  = _desc->power;
	m_hitRadius = _desc->hitRadius;
	m_detectionRadius = _desc->detectionRadius; 
	m_battleState = BATTLE_STATE_WEAK;
	m_isAggro = false;
	m_target = nullptr;


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
	m_hp -= _col.hitObj->GetComponent<AttackInfo>()->m_power;
}

void BnS_Enemy::OnTriggerExit(Collision & _col)
{
}
