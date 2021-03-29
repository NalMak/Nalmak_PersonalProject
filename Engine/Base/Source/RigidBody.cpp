#include "RigidBody.h"
#include "Nalmak_Include.h"
#include "transform.h"
#include "PhysicsManager.h"

RigidBody::RigidBody(Desc * _desc)
{
	m_density = _desc->density;
	m_damping = _desc->damping;
	m_isGravity = _desc->isGravity;
	m_isKinematic = _desc->isKinematic;

}

RigidBody::~RigidBody()
{
}

void RigidBody::Initialize()
{
}

void RigidBody::Update()
{
}

void RigidBody::LateUpdate()
{
	if (m_gameObject->IsStatic())
		return;

	m_transform->position = GetWorldPosition();
	m_transform->rotation = GetWorldRotation();
}



void RigidBody::Release()
{
	PhysicsManager::GetInstance()->RemoveActorFromScene(m_rigid);
}

void RigidBody::OnEnable()
{
	m_rigid->wakeUp();
}

void RigidBody::OnDisable()
{
	m_rigid->putToSleep();
}

void RigidBody::AddForce(const Vector3 & _force)
{
	m_rigid->addForce(PxVec3(_force.x, _force.y, _force.z));
}

void RigidBody::AddVelocity(const Vector3 & _velocity)
{
	m_rigid->setLinearVelocity(m_rigid->getLinearVelocity() + PxVec3(_velocity.x, _velocity.y, _velocity.z));
}

void RigidBody::SetVelocity(const Vector3 & _velocity)
{
	m_rigid->setLinearVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
}

void RigidBody::AddAngularVelocity(const Vector3 & _velocity)
{
	m_rigid->addTorque(PxVec3(_velocity.x, _velocity.y, _velocity.z));
}

void RigidBody::SetAngularVelocity(const Vector3 & _velocity)
{
	m_rigid->setAngularVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
}

void RigidBody::SetGravity(bool _gravity)
{
}

void RigidBody::SetWorldPosition(const Vector3 & _pos)
{
	if (!m_rigid)
		return;

	Quaternion rot = m_transform->GetWorldRotation();
	PxTransform trs;
	trs.p = { _pos.x, _pos.y, _pos.z };
	trs.q = { rot.x,rot.y,rot.z,rot.w };
	m_rigid->setGlobalPose(trs);
	
}



Vector3 RigidBody::GetVelocity()
{
	auto velocity = m_rigid->getLinearVelocity();
	return { velocity.x,velocity.y,velocity.z };
}

Vector3 RigidBody::GetAngularVelocity()
{
	auto velocity = m_rigid->getAngularVelocity();
	return{ velocity.x,velocity.y,velocity.z };
}

void RigidBody::SetRigidBody(PxRigidDynamic * _rigid)
{
	m_rigid = _rigid;
}

void RigidBody::SetTrigger(bool _trigger)
{
	PxShape* shape = nullptr;
	m_rigid->getShapes(&shape, 1);

	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_trigger);

}

void RigidBody::SetWorldTransform()
{
	auto pos = m_transform->GetWorldPosition();
	auto rot = m_transform->GetWorldRotation();
	PxTransform trs;
	trs.p = { pos.x, pos.y, pos.z };
	trs.q = { rot.x,rot.y,rot.z,rot.w };
	m_rigid->setGlobalPose(trs);
}

void RigidBody::SetWorldRotation(const Quaternion& _rot)
{
	auto pos = m_transform->GetWorldPosition();
	auto rot = _rot;
	PxTransform trs;
	trs.p = { pos.x, pos.y, pos.z };
	trs.q = { rot.x,rot.y,rot.z,rot.w };
	m_rigid->setGlobalPose(trs);
}

void RigidBody::SetWorldPositionAndRotation(const Vector3 & _pos, const Quaternion & _rot)
{
	auto pos = _pos;
	auto rot = _rot;
	PxTransform trs;
	trs.p = { pos.x, pos.y, pos.z };
	trs.q = { rot.x,rot.y,rot.z,rot.w };
	m_rigid->setGlobalPose(trs);
}

Vector3 RigidBody::GetWorldPosition()
{
	auto pos = m_rigid->getGlobalPose().p;

	return Vector3(pos.x, pos.y, pos.z);
}

Quaternion RigidBody::GetWorldRotation()
{
	auto rot = m_rigid->getGlobalPose().q;

	return Quaternion(rot.x, rot.y, rot.z, rot.w);
}

PxRigidDynamic * RigidBody::GetRigidBody()
{
	return m_rigid;
}

float RigidBody::GetDensity()
{
	return m_density;
}

float RigidBody::GetDamping()
{
	return m_damping;
}

bool RigidBody::IsGravity()
{
	return m_isGravity;
}

bool RigidBody::IsKinematic()
{
	return m_isKinematic;
}
