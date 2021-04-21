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

bool CharacterController::IsGround()
{
	PxControllerState state;
	m_controller->getState(state);
	return state.isMovingUp;
}

void CharacterController::Move(const Vector3 & _velocity)
{
	PxVec3 vec(_velocity.x, _velocity.y, _velocity.z);

	PxControllerFilters filter;
	m_controller->move(vec, 0.01f, dTime, PxControllerFilters());
}

void CharacterController::Move(float _x,float _y, float _z)
{
	PxVec3 vec(_x, _y, _z);

	PxControllerFilters filter;
	m_controller->move(vec, 0.0f, dTime, PxControllerFilters());
}