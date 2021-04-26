#pragma once
#include "Component.h"
#include "PhysicsManager.h"

class NALMAK_DLL Collider abstract :
	public Component
{
public:
	Collider(bool _isTrigger,const Vector3& _posOffset, const Quaternion& _rotOffset);
	virtual ~Collider();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual void Update()  = 0;
	virtual void Release();
protected:
	class RigidBody* m_rigid = nullptr;

protected:
	bool m_isTrigger;
	Vector3 m_offset;
	Quaternion m_rotOffset;
	PxShape* m_shape = nullptr;
public:
	void UpdatePysicsTransform();
	void SetShape(PxShape* _shape);
	PxShape* GetShape();

	void SetTrigger(bool _isTrigger);
	bool IsTrigger() { return m_isTrigger; }
	const Vector3& GetPosOffset() { return m_offset; }
	const Quaternion& GetRotOffset() { return m_rotOffset; }
	void SetPosOffset(const Vector3& _pos);
	void SetPosX(float _x);
	void SetPosY(float _y);
	void SetPosZ(float _z);

};

