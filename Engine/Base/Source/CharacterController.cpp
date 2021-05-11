#include "CharacterController.h"
#include "Transform.h"



CharacterController::CharacterController(Desc * _desc)
{
	PxCapsuleClimbingMode::Enum climbingMode = PxCapsuleClimbingMode::eEASY;

	m_radius = _desc->radius;
	m_height = _desc->height;
	m_center = _desc->center;
	m_slopeLimit = _desc->slopeLimit;
	m_skinWidth = _desc->skinWidth;
	m_stepOffset = _desc->stepOffset;
	m_climbingMode = _desc->climbingMode;
	m_velocity = { 0,0,0 };
}

CharacterController::~CharacterController()
{
}

void CharacterController::Initialize()
{
	m_controller = PhysicsManager::GetInstance()->CreateCharacterController(this);
	m_filterCallback = new NalmakPxControllerFilterCallback;
	m_filterData = PhysicsManager::GetInstance()->GetFilterData(m_gameObject->GetLayer());
}

void CharacterController::Update()
{
	
}

void CharacterController::LateUpdate()
{
	PxVec3 vec(m_velocity.x, m_velocity.y, m_velocity.z);

	PxControllerFilters filter;

	filter.mCCTFilterCallback = m_filterCallback;
	filter.mFilterData = &m_filterData;
	filter.mFilterFlags = physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC;
	m_preFlag = m_curFlag;
	m_curFlag = m_controller->move(vec * dTime, 0.0f, dTime, filter);
}

void CharacterController::PreRender()
{
	PxExtendedVec3 pos = m_controller->getPosition();
	m_transform->position = Vector3{ (float)pos.x,(float)pos.y,(float)pos.z } - m_center;
}

void CharacterController::Release()
{
	Safe_release(m_controller);
	SAFE_DELETE(m_filterCallback);
}

void CharacterController::SetFootPosition(const Vector3 & _pos)
{
	PxExtendedVec3 vec3 = { _pos.x,_pos.y,_pos.z };
	m_controller->setFootPosition(vec3);
}

void CharacterController::SetVelocity(const Vector3 & _velocity)
{
	m_velocity = _velocity;
}

void CharacterController::SetVelocity(float _x, float _y, float _z)
{
	m_velocity = { _x,_y,_z };
}

void CharacterController::AddVelocity(const Vector3 & _velocity)
{
	m_velocity += _velocity;
}

void CharacterController::AddVelocity(float _x, float _y, float _z)
{
	m_velocity += { _x,_y,_z };
}

void CharacterController::SetVelocityX(float _x)
{
	m_velocity.x = _x;
}

void CharacterController::SetVelocityY(float _y)
{
	m_velocity.y = _y;
}

void CharacterController::SetVelocityZ(float _z)
{
	m_velocity.z = _z;
}

void CharacterController::SetPhysicsPosition(const Vector3 & _pos)
{
	Vector3 pos = _pos - m_transform->GetWorldPosition();

	m_velocity = { 0,0,0 };
	PxVec3 vec(pos.x,0, pos.z);

	m_controller->move(vec * dTime, 0.0f, dTime, PxControllerFilters());
}

bool CharacterController::IsGround()
{
	return m_curFlag & PxControllerCollisionFlag::eCOLLISION_DOWN;
}

bool CharacterController::IsSide()
{
	return  m_curFlag & PxControllerCollisionFlag::eCOLLISION_SIDES;
}

void CharacterController::SetHalfHeight(float _height)
{
	m_controller->setHeight(_height);
}

const Vector3 & CharacterController::GetVelocity()
{
	return m_velocity;
}
