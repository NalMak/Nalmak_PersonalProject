#include "Collider.h"
#include "Transform.h"



Collider::Collider(bool _isTrigger,const Vector3& _posOffset)
{
	m_offset = _posOffset;
	m_isTrigger = _isTrigger;
}


Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
}

void Collider::Release()
{
	m_shape->getActor()->detachShape(*m_shape);
}


void Collider::UpdatePysicsTransform()
{
	PxTransform trs = m_shape->getActor()->getGlobalPose();
	
	Vector3 pos = m_transform->GetWorldPosition();
	Quaternion rot = m_transform->GetWorldRotation();
	trs.p.x = pos.x;
	trs.p.y = pos.y;
	trs.p.z = pos.z;

	trs.q.x = rot.x;
	trs.q.y = rot.y;
	trs.q.z = rot.z;
	trs.q.w = rot.w;

	m_shape->getActor()->setGlobalPose(trs);
}

void Collider::SetShape(PxShape * _shape)
{
	m_shape = _shape;
}

PxShape * Collider::GetShape()
{
	return m_shape;
}

void Collider::SetTrigger(bool _isTrigger)
{
	m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_isTrigger);
	m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _isTrigger);
}

void Collider::SetPosOffset(const Vector3& _pos)
{
	m_offset = _pos;
	PxTransform trs = m_shape->getLocalPose();
	trs.p.x = m_offset.x;
	trs.p.y = m_offset.y;
	trs.p.z = m_offset.z;

	m_shape->setLocalPose(trs);
}

void Collider::SetPosX(float _value)
{
	m_offset.x = _value;
	PxTransform trs =  m_shape->getLocalPose();
	trs.p.x = _value;
	m_shape->setLocalPose(trs);
}

void Collider::SetPosY(float _value)
{
	m_offset.y = _value;
	PxTransform trs = m_shape->getLocalPose();
	trs.p.y = _value;
	m_shape->setLocalPose(trs);
}

void Collider::SetPosZ(float _value)
{
	m_offset.z = _value;
	PxTransform trs = m_shape->getLocalPose();
	trs.p.z = _value;
	m_shape->setLocalPose(trs);
}