#include "stdafx.h"
#include "BnS_Enemy.h"
#include "BnS_DamageFont.h"
#include "LynInfo.h"


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

	CalcWorldVolume();
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
			auto attackInfo = _col.hitObj->GetComponent<AttackInfo>();
			GetDamage(attackInfo);
			
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

const RECT & BnS_Enemy::GetScreenVolume()
{
	return m_screenVolumeRect;
}

GameObject * BnS_Enemy::GetTarget()
{
	return m_target;
}

void BnS_Enemy::LostTarget()
{
	m_target = nullptr;
}

void BnS_Enemy::GetDamage(AttackInfo * _attackInfo)
{
	m_hp -= _attackInfo->m_power;

	if (_attackInfo->m_innerPower > 0)
		_attackInfo->GetHost()->GetComponent<LynInfo>()->AddInnerPower(_attackInfo->m_innerPower);


	BnS_DamageFont::Desc damageFont;
	damageFont.damage = _attackInfo->m_power;
	damageFont.isCritical =_attackInfo->m_isCritical;
	INSTANTIATE()->AddComponent<BnS_DamageFont>(&damageFont)->SetPosition(m_transform->GetWorldPosition() + Vector3(0, 6, 0));
}

void BnS_Enemy::CalcWorldVolume()
{
	auto cam = Core::GetInstance()->GetMainCamera();
	Vector3 pos = m_transform->GetWorldPosition();
	float averageX = (m_volumeRect.z - m_volumeRect.x) * 0.5f;
	float averageY = (m_volumeRect.w - m_volumeRect.y) * 0.5f;
	pos += Vector3(averageX, -averageY, 0);

	Vector2 leftTopPos = cam->WorldToScreenPos(pos - cam->GetTransform()->GetRight() * m_volumeRect.x + cam->GetTransform()->GetUp() * m_volumeRect.y);
	Vector2 rightBottomPos = cam->WorldToScreenPos(pos + cam->GetTransform()->GetRight() * m_volumeRect.z - cam->GetTransform()->GetUp() * m_volumeRect.w);
	m_screenVolumeRect.left = (UINT)leftTopPos.x;
	m_screenVolumeRect.top = (UINT)leftTopPos.y;
	m_screenVolumeRect.right = (UINT)rightBottomPos.x;
	m_screenVolumeRect.bottom = (UINT)rightBottomPos.y;
}
