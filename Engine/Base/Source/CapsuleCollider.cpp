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
