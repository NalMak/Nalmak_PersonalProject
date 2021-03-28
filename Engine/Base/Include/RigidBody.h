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
		float density = 1;
		float damping = 1;
		bool isGravity = true;
		bool isKinematic = false;
	};
public:
	RigidBody(Desc* _desc);
	~RigidBody();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

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
public:
	Vector3 GetWorldPosition();
	Quaternion GetWorldRotation();
public:
	PxRigidDynamic* GetRigidBody();
private:
	PxRigidDynamic* m_rigid;
	float m_density;
	float m_damping;
	bool  m_isGravity;
	bool  m_isKinematic;
public:
	float GetDensity();
	float GetDamping();
	bool IsGravity();
	bool IsKinematic();
};

