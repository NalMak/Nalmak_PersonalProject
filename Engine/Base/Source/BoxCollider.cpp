#include "BoxCollider.h"

#include "RigidBody.h"
#include "MeshRenderer.h"

BoxCollider::BoxCollider(Desc * _desc)
	: Collider(_desc->isTrigger)
{
	m_width = _desc->width;
	m_height = _desc->height;
	m_depth = _desc->depth;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Initialize()
{
	m_rigid = GetComponent<RigidBody>();
	PhysicsManager::GetInstance()->CreateBoxCollider(this, m_rigid, m_width,m_height,m_depth);


}

void BoxCollider::Update()
{
}
