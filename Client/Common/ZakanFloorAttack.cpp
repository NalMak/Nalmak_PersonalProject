#include "stdafx.h"
#include "ZakanFloorAttack.h"
#include "AttackInfo.h"


ZakanFloorAttack::ZakanFloorAttack(Desc * _desc)
{
	m_host = _desc->host;
}

ZakanFloorAttack::~ZakanFloorAttack()
{
}

void ZakanFloorAttack::Initialize()
{
	m_material = GetComponent<MeshRenderer>()->GetMaterial();

	m_explosionTimer = 2.f;

	m_floatSpeed = Nalmak_Math::Rand(0.8f, 1.2f);

	m_currentUV_X = 0;
}

void ZakanFloorAttack::Update()
{
	m_explosionTimer -= dTime;

	if (m_explosionTimer < 0)
	{
		Explosion();
		DESTROY(m_gameObject);
	}

	m_currentUV_X += m_floatSpeed;
}

void ZakanFloorAttack::EachRender()
{
	m_material->SetFloat("g_uvAnimX", m_currentUV_X);
}

void ZakanFloorAttack::Explosion()
{
	AttackInfo::Desc info;
	info.attackType = ATTACK_TYPE_DOWN;
	info.colliderType = COLLIDER_TYPE_CAPSULE;
	info.radius = m_transform->scale.x * 0.5f;
	info.height = 10.f;
	info.power = 3000;
	info.host = m_host;
	auto hitBox = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_ENEMY_HITBOX)->AddComponent<AttackInfo>(&info);

	hitBox->SetPosition(m_transform->GetWorldPosition());
	hitBox->SetRotation(m_transform->GetWorldRotation());
}

