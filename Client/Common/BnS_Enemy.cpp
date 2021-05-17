#include "stdafx.h"
#include "BnS_Enemy.h"
#include "BnS_DamageFont.h"
#include "LynInfo.h"
#include "EnemyStateControl.h"
#include "UIManager.h"

BnS_Enemy::BnS_Enemy(Desc * _desc)
{
	m_hp = _desc->hp;
	m_maxHp = m_hp;
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
	m_stateControl = GetComponent<EnemyStateControl>();
	m_audio = GetComponent<AudioSource>();
	m_spawnPos = m_transform->GetWorldPosition();
	m_spawnRot = m_transform->GetWorldRotation();
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
			if (Nalmak_Math::Distance(player->GetTransform()->GetWorldPosition(), m_transform->GetWorldPosition()) * BNS_DISTANCE_RATIO < 9.f)
			{
				if(player->GetComponent<LynInfo>()->GetBattleState() == BATTLE_STATE_DEAD)
					continue;
				m_target = player;
				break;
			}
		}
	}
	else
	{
		m_distanceToTarget = Nalmak_Math::Distance(m_transform->GetWorldPosition(), m_target->GetTransform()->GetWorldPosition()) * BNS_DISTANCE_RATIO;
	}
}

void BnS_Enemy::OnTriggerEnter(Collision & _col)
{
	if (_col.hitObj->GetTag() == OBJECT_TAG_ATTACKINFO)
	{
		if (_col.hitObj->GetLayer() == OBJECT_LAYER_PLAYER_HITBOX)
		{
			auto attackInfo = _col.hitObj->GetComponent<AttackInfo>();

			if (attackInfo->m_hitEvent)
				(*attackInfo->m_hitEvent)();
			if (attackInfo->m_innerPower > 0)
				attackInfo->GetHost()->GetComponent<LynInfo>()->AddInnerPower(attackInfo->m_innerPower);

			if (m_battleState == BATTLE_STATE_WEAK)
			{
				auto type = attackInfo->m_attackType;
				switch (type)
				{
				case ATTACK_TYPE_DEFAULT:
					break;
				case ATTACK_TYPE_DOWN:
					m_audio->PlayOneShot(L"down_attack");

					m_stateControl->SetFloat(L"down", attackInfo->m_ccTime);
					m_stateControl->SetState(L"down");
					break;
				case ATTACK_TYPE_GROGY:
					m_audio->PlayOneShot(L"grogy_attack");

					break;
				case ATTACK_TYPE_STUN:
					m_audio->PlayOneShot(L"stun_attack");

					break;
				case ATTACK_TYPE_MAGNETIC:
					break;
				case ATTACK_TYPE_AIR:
					break;
				case ATTACK_TYPE_MAX:
					break;
				default:
					break;
				}
				
			}
			if (attackInfo->m_attackType == ATTACK_TYPE_AIR)
			{
				m_stateControl->SetState(L"air");
			}
			GetDamage(attackInfo);
			
		}
	}
}

void BnS_Enemy::OnTriggerExit(Collision & _col)
{
}

BATTLE_STATE BnS_Enemy::GetBattleState()
{
	return m_battleState;
}

void BnS_Enemy::SetBattleState(BATTLE_STATE _state)
{
	if (m_battleState != _state)
	{
		m_battleState = _state;
	}
}

const Vector3 & BnS_Enemy::GetSpawnPos()
{
	return m_spawnPos;
}

const Quaternion & BnS_Enemy::GetSpawnRot()
{
	return m_spawnRot;
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

float BnS_Enemy::GetDistanceToTarget()
{
	return m_distanceToTarget;
}

void BnS_Enemy::LostTarget()
{
	m_target = nullptr;
	m_stateControl->SetState(L"move");
}

void BnS_Enemy::LookTarget()
{
	Vector3 targetPos;
	if (!m_target)
	{
		targetPos = m_spawnPos;
	}
	else
	{
		targetPos = GetTarget()->GetTransform()->GetWorldPosition();
	}
	Vector3 dir = targetPos - m_transform->GetWorldPosition();
	dir = Nalmak_Math::Normalize(dir);
	float angle = acosf(Nalmak_Math::Dot(dir, Vector3(0, 0, 1)));


	Quaternion rot;
	if (Nalmak_Math::Cross(dir, Vector3(0, 0, 1)).y > 0)
		D3DXQuaternionRotationYawPitchRoll(&rot, -angle, 0, 0);
	else
		D3DXQuaternionRotationYawPitchRoll(&rot, angle, 0, 0);

	m_transform->rotation = rot;
	
}

void BnS_Enemy::GetDamage(AttackInfo * _attackInfo)
{
	m_hp -= _attackInfo->m_power;
	
	BnS_DamageFont::Desc damageFont;
	damageFont.damage = _attackInfo->m_power;
	damageFont.isCritical =_attackInfo->m_isCritical;
	if(_attackInfo->m_isCritical)
		damageFont.animationType = DAMAGE_FONT_ANIMATION_TYPE_EMPHASIS;
	else
		damageFont.animationType = DAMAGE_FONT_ANIMATION_TYPE_FALLING;

	INSTANTIATE()->AddComponent<BnS_DamageFont>(&damageFont)->SetPosition(m_transform->GetWorldPosition() + Vector3(0, 6, 0));

	if (m_hp < 0)
	{
		m_hp = 0;
		UIManager::GetInstance()->UpdateEnemyHpUI((float)m_hp / m_maxHp);
		m_stateControl->SetState(L"dead");
		return;
	}
	UIManager::GetInstance()->UpdateEnemyHpUI((float)m_hp / m_maxHp);
}

float BnS_Enemy::GetHpRatio()
{
	return  (float)m_hp / m_maxHp;
}

void BnS_Enemy::Reset()
{
	m_target = nullptr;

	m_hp = m_maxHp;
	UIManager::GetInstance()->UpdateEnemyHpUI(1);
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
