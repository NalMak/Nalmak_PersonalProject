#pragma once
#include "Component.h"
#include "PhysicsManager.h"

// Only work in static mesh collider
class NALMAK_DLL CharacterController :
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
		bool isGravity = true;
		PxCapsuleClimbingMode::Enum climbingMode = PxCapsuleClimbingMode::eCONSTRAINED;
	};
public:
	CharacterController(Desc* _desc);
	~CharacterController();

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Release() override;
public:
	void SetVelocity(const Vector3& _velocity);
	void SetVelocity(float _x,float _y, float _z);
	void AddVelocity(float _x, float _y, float _z);

	void SetVelocityX(float _x);
	void SetVelocityY(float _y);
	void SetVelocityZ(float _z);


	bool IsGround();
	void SetHalfHeight(float _height);
	void Move(const Vector3& _velocity);
	void Move(float _x, float _y, float _z);
public:
	const Vector3& GetVelocity();
private:
	float m_radius;
	float m_height;
	Vector3 m_center;
	Vector3 m_velocity;

	float m_slopeLimit;
	float m_skinWidth;
	float m_stepOffset;
	float m_stepLimit;
	PxCapsuleClimbingMode::Enum m_climbingMode;

	PxCapsuleController* m_controller;
};

