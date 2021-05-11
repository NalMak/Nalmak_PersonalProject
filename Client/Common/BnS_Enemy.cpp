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
	m_character = GetComponent<CharacterController>();
}

void BnS_Enemy::Update()
{
	DEBUG_LOG(L"enemy hp", m_hp);

	m_character->AddVelocity(0, -50.f * dTime, 0);

	if (!m_target)
	{
		auto playerList = Core::GetInstance()->GetObjectList(OBJECT_TAG_PLAYER);
		for (auto& player : playerList)
		{
			if (Nalmak_Math::Distance(player->GetTransform()->GetWorldPosition(), m_transform->GetWorldPosition()) < 5.f)
			{
				m_target = player;
			}
		}
	}
	
}

void BnS_Enemy::OnTriggerEnter(Collision & _col)
{
	if (_col.hitObj->GetTag() == OBJECT_TAG_ATTACKINFO)
	{
		if (_col.hitObj->GetLayer() == OBJECT_LAYER_PLAYER_HITBOX)
		{
			m_hp -= _col.hitObj->GetComponent<AttackInfo>()->m_power;

			BnS_DamageFont::Desc damageFont;
			damageFont.damage = Nalmak_Math::Rand(80, 120);
			damageFont.isCritical = Nalmak_Math::Random<bool>(true, true, true, false, false);
			INSTANTIATE()->AddComponent<BnS_DamageFont>(&damageFont)->SetPosition(m_transform->GetWorldPosition() + Vector3(0, 6, 0));
		}
	}
}

void BnS_Enemy::OnTriggerExit(Collision & _col)
{
}

const Vector4 & BnS_Enemy::GetVolume()
{
	return m_volumeRect;	
}

GameObject * BnS_Enemy::GetTarget()
{
	return m_target;
}

void BnS_Enemy::LostTarget()
{
	m_target = nullptr;
}
