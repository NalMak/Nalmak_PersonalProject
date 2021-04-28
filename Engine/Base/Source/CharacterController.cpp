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
	m_isGravity = _desc->isGravity;
	m_velocity = { 0,0,0 };
}

CharacterController::~CharacterController()
{
}

void CharacterController::Initialize()
{
	m_controller = PhysicsManager::GetInstance()->CreateCharacterController(this);
}

void CharacterController::Update()
{
	if(m_isGravity)
	{
		if (!IsGround())
			m_velocity += Vector3(0, -30.f * dTime, 0);
	}
	Move(m_velocity);
	DEBUG_LOG(L"Character velocity", m_velocity);
	//m_controller->move(vec * dTime, 0.0f, dTime, PxControllerFilters());
}

void CharacterController::LateUpdate()
{
	PxExtendedVec3 pos = m_controller->getPosition();
	m_transform->position = Vector3{ (float)pos.x,(float)pos.y,(float)pos.z } - m_center;
}

void CharacterController::Release()
{
	Safe_release(m_controller);
}

void CharacterController::SetVelocity(const Vector3 & _velocity)
{
	m_velocity = _velocity;
}

void CharacterController::SetVelocity(float _x, float _y, float _z)
{
	m_velocity = { _x,_y,_z };
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

bool CharacterController::IsGround()
{
	PxControllerState state;
	m_controller->getState(state);
	if (state.touchedShape)
		return true;
	return false;
}

void CharacterController::SetHalfHeight(float _height)
{
	m_controller->setHeight(_height);
}

void CharacterController::Move(const Vector3 & _velocity)
{
	PxVec3 vec(_velocity.x, _velocity.y, _velocity.z);

	PxControllerFilters filter;
	m_controller->move(vec * dTime, 0.0f, dTime, PxControllerFilters());
}

void CharacterController::Move(float _x,float _y, float _z)
{
	PxVec3 vec(_x, _y, _z);

	PxControllerFilters filter;
	m_controller->move(vec * dTime, 0.0f, dTime, PxControllerFilters());
}