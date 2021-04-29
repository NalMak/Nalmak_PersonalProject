#include "RigidBody.h"
#include "Nalmak_Include.h"
#include "transform.h"
#include "PhysicsManager.h"
#include "RenderInfo.h"


RigidBody::RigidBody(Desc * _desc)
{
	m_damping = _desc->damping;
	m_isGravity = _desc->isGravity;
	m_isKinematic = _desc->isKinematic;
	m_constraints = _desc->constraints;
	m_mass = _desc->mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Initialize()
{
	PhysicsManager::GetInstance()->CreateRigidDynamic(this);
}

void RigidBody::Update()
{
	SetWorldTransform();
}

void RigidBody::LateUpdate()
{

}

void RigidBody::PreRender()
{
	if (!m_rigid)
		return;

	if (m_isKinematic)
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
	//PhysicsManager::GetInstance()->RemoveActorFromScene(m_rigid);
}

void RigidBody::OnDisable()
{
	//PhysicsManager::GetInstance()->AddActorToScene(m_rigid);
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


float RigidBody::GetDamping()
{
	return m_damping;
}

float RigidBody::GetMass()
{
	return m_mass;
}

bool RigidBody::IsGravity()
{
	return m_isGravity;
}

bool RigidBody::IsKinematic()
{
	return m_isKinematic;
}
