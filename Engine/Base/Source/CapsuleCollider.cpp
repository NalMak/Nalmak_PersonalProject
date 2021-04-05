#include "CapsuleCollider.h"

#include "RigidBody.h"


CapsuleCollider::CapsuleCollider(Desc * _desc)
	: Collider(_desc->isTrigger, _desc->posOffset)
{
	m_height = _desc->height;
	m_radius = _desc->radius;
}

CapsuleCollider::~CapsuleCollider()
{
}

void CapsuleCollider::Initialize()
{
	m_rigid = GetComponent<RigidBody>();
	PhysicsManager::GetInstance()->CreateCapsuleCollider(this, m_rigid,m_radius,m_height);
}

void CapsuleCollider::Update()
{
}

void CapsuleCollider::SetRadius(float _radius)
{
	m_radius = _radius;
	PxCapsuleGeometry capsule;
	m_shape->getCapsuleGeometry(capsule);
	capsule.radius = _radius;
	m_shape->setGeometry(capsule);
}

void CapsuleCollider::SetHeight(float _height)
{
	m_height = _height;
	PxCapsuleGeometry capsule;
	m_shape->getCapsuleGeometry(capsule);
	capsule.halfHeight = _height * 0.5f;
	m_shape->setGeometry(capsule);

}


