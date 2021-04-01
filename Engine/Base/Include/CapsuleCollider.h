#pragma once
#include "Collider.h"
class NALMAK_DLL CapsuleCollider : public Collider
{
public:
	struct Desc
	{
		float radius = 0.5f;
		float height = 1;
		Vector3 posOffset = { 0,0,0 };
		bool isTrigger = false;
	};
public:
	CapsuleCollider(Desc* _desc);
	~CapsuleCollider();
private:
	// Collider을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_radius;
	float m_height;
};

