#pragma once
#include "Component.h"
#include "PhysicsManager.h"

class NALMAK_DLL Collider :
	public Component
{
public:
	Collider(bool _isTrigger);
	virtual ~Collider();

private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() = 0;
	virtual void Update()  = 0;
protected:
	class RigidBody* m_rigid = nullptr;

protected:
	bool m_isTrigger;

public:
	bool IsTrigger() { return m_isTrigger; }
};

