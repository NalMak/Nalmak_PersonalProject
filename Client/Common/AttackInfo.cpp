#include "stdafx.h"
#include "AttackInfo.h"




AttackInfo::AttackInfo(Desc * _desc)
{
	m_attackType = _desc->attackType;
	m_isCritical = _desc->isCritical;
	m_power = _desc->power;
	m_innerPower = _desc->innerPower;
	m_ccTime = _desc->ccTime;
	m_hitEvent = nullptr;

	
	m_lifeTime = _desc->lifeTime;
	assert(L"Please Set Attack host!" && _desc->host);

	m_host = _desc->host;
	m_radius = _desc->radius;
	m_width = _desc->width;
	m_height = _desc->height;
	m_depth = _desc->depth;
	m_colliderType = _desc->colliderType;
	m_soundName = _desc->soundName;
}

AttackInfo::~AttackInfo()
{
}

void AttackInfo::Initialize()
{
	switch (m_colliderType)
	{
	case COLLIDER_TYPE_SPHERE:
	{
		SphereCollider::Desc sphere;
		sphere.radius = m_radius;
		sphere.isTrigger = true;
		AddComponent<SphereCollider>(&sphere);
		break;
	}
	case COLLIDER_TYPE_BOX:
	{
		BoxCollider::Desc box;
		box.height = m_height;
		box.depth = m_depth;
		box.width = m_width;
		box.isTrigger = true;
		AddComponent<BoxCollider>(&box);
		break;
	}
	case COLLIDER_TYPE_CAPSULE:
	{
		CapsuleCollider::Desc capsule;
		capsule.height = m_height;
		capsule.radius = m_radius;
		capsule.isTrigger = true;
		AddComponent<CapsuleCollider>(&capsule);
		break;
	}
	default:
		break;
	}
	
}

void AttackInfo::Update()
{
	if (m_lifeTime > 0)
	{
		m_lifeTime -= dTime;
		if (m_lifeTime <= 0)
		{
			DESTROY(m_gameObject);
		}
	}
}

void AttackInfo::Release()
{
	SAFE_DELETE(m_hitEvent);
}


void AttackInfo::AddHitEvent(HitEvent _hitEvent)
{
	m_hitEvent = new HitEvent(_hitEvent);
}

GameObject * AttackInfo::GetHost()
{
	return m_host;
}
