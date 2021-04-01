#pragma once
#include "Component.h"
#include "PxPhysicsAPI.h"

using namespace physx;

class NALMAK_DLL RigidBody :
	public Component
{
public:
	struct Desc
	{
		float damping = 0.1f;
		float mass = 1;
		bool isGravity = true;
		bool isKinematic = false;

		BitFlag<CONSTRAINTS_DIRECTION> constraints = 0;
	};
public:
	RigidBody(Desc* _desc);
	~RigidBody();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
public:
	void AddForce(const Vector3& _force);
	void AddVelocity(const Vector3& _force);
	void SetVelocity(const Vector3& _force);
	void AddAngularVelocity(const Vector3& _force);
	void SetAngularVelocity(const Vector3& _force);
	void SetGravity(bool _gravity);
public:
	Vector3 GetVelocity();
	Vector3 GetAngularVelocity();

public:
	void SetRigidBody(PxRigidDynamic* _rigid);
	void SetTrigger(bool _trigger);
	void SetWorldTransform();
	void SetWorldPosition(const Vector3& _pos);
	void SetWorldRotation(const Quaternion& _rot);
	void SetWorldPositionAndRotation(const Vector3& _pos, const Quaternion& _rot);

public:
	Vector3 GetWorldPosition();
	Quaternion GetWorldRotation();
public:
	PxRigidDynamic* GetRigidBody();
private:
	PxRigidDynamic* m_rigid;
	float m_damping;
	float m_mass;
	bool  m_isGravity;
	bool  m_isKinematic;
	BitFlag<CONSTRAINTS_DIRECTION> m_constraints;
public:
	float GetDamping();
	float GetMass();
	bool IsGravity();
	bool IsKinematic();
};

