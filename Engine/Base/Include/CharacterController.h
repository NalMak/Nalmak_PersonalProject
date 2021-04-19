#pragma once
#include "Component.h"
#include "PhysicsManager.h"

// Only work in static mesh collider
class CharacterController :
	public Component
{
	friend class PhysicsManager;
public:
	struct Desc
	{
		float radius = 1.f;
		float height = 1.f;
		Vector3 center = { 0,0,0 };

		float slopeLimit = 45;
		float skinWidth = 0.01f;
		float stepOffset = 0.1f;
		float stepLimit = 0.01f;
		PxCapsuleClimbingMode::Enum climbingMode = PxCapsuleClimbingMode::eCONSTRAINED;
	};
public:
	CharacterController(Desc* _desc);
	~CharacterController();

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
private:
	float m_radius;
	float m_height;
	Vector3 m_center;

	float m_slopeLimit;
	float m_skinWidth;
	float m_stepOffset;
	float m_stepLimit;
	PxCapsuleClimbingMode::Enum m_climbingMode;

	PxController* m_controller;
};

