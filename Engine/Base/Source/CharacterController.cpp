#include "CharacterController.h"




CharacterController::CharacterController(Desc * _desc)
{
	float radius = 1.f;
	float height = 1.f;
	Vector3 center = { 0,0,0 };

	float slopeLimit = 45;
	float skinWidth = 0.01f;
	float stepOffset = 0.1f;
	float stepLimit = 0.01f;
	PxCapsuleClimbingMode::Enum climbingMode = PxCapsuleClimbingMode::eEASY;

	m_radius = _desc->radius;
	m_height = _desc->height;
	m_center = _desc->center;
	m_slopeLimit = _desc->slopeLimit;
	m_skinWidth = _desc->skinWidth;
	m_stepOffset = _desc->stepOffset;
	m_stepLimit = _desc->stepLimit;
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

void CharacterController::Release()
{
	Safe_release(m_controller);
}
