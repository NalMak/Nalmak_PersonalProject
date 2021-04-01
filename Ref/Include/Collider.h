#pragma once
#include "Component.h"
#include "PhysicsManager.h"

class NALMAK_DLL Collider :
	public Component
{
public:
	Collider(bool _isTrigger, const Vector3& _posOffset);
	virtual ~Collider();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual void Update()  = 0;
protected:
	class RigidBody* m_rigid = nullptr;

protected:
	bool m_isTrigger;
	Vector3 m_offset;
public:
	bool IsTrigger() { return m_isTrigger; }
	const Vector3& GetPosOffset() { return m_offset; }
};

