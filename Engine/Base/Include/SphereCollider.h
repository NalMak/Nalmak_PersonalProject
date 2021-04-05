#pragma once
#include "Collider.h"

class NALMAK_DLL SphereCollider :
	public Collider
{
public:
	struct Desc
	{
		float radius = 0.5f;
		Vector3 posOffset = { 0,0,0 };
		bool isTrigger = false;
	};
public:
	SphereCollider(Desc* _desc);
	~SphereCollider();

	// Collider을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	float GetRadius() { return m_radius; }
	void SetRadius(float _radius);
private:
	float m_radius;


};

