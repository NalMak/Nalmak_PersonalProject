#include "BoxCollider.h"

#include "RigidBody.h"
#include "MeshRenderer.h"

BoxCollider::BoxCollider(Desc * _desc)
	: Collider(_desc->isTrigger,_desc->posOffset)
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

void BoxCollider::SetWidth(float _value)
{
	m_width = _value;
	PxBoxGeometry box;
	m_shape->getBoxGeometry(box);
	box.halfExtents.x = _value* 0.5f;
	m_shape->setGeometry(box);
}

void BoxCollider::SetHeight(float _value)
{
	m_height = _value;
	PxBoxGeometry box;
	m_shape->getBoxGeometry(box);
	box.halfExtents.y = _value * 0.5f;
	m_shape->setGeometry(box);
}

void BoxCollider::SetDepth(float _value)
{
	m_depth = _value;
	PxBoxGeometry box;
	m_shape->getBoxGeometry(box);
	box.halfExtents.z = _value* 0.5f;
	m_shape->setGeometry(box);
}

