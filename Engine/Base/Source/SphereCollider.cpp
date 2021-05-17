#include "SphereCollider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"


SphereCollider::SphereCollider(Desc * _desc)
	: Collider(_desc->isTrigger,_desc->posOffset,*D3DXQuaternionRotationYawPitchRoll(&Quaternion(), _desc->rotOffset.x, _desc->rotOffset.y,_desc->rotOffset.z))
{
	m_radius = _desc->radius;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
	m_rigid = GetComponent<RigidBody>();
	PhysicsManager::GetInstance()->CreateSphereCollider(this,m_rigid,m_radius);

}

void SphereCollider::Update()
{
}

void SphereCollider::SetRadius(float _radius)
{
	m_radius = _radius;
	PxSphereGeometry sphere;
	m_shape->getSphereGeometry(sphere);
	sphere.radius = _radius;
	m_shape->setGeometry(sphere);
}
