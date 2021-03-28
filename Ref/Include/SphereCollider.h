#pragma once
#include "Collider.h"

class NALMAK_DLL SphereCollider :
	public Collider
{
public:
	struct Desc
	{
		float radius = 0.5f;
		bool isTrigger = false;
	};
public:
	SphereCollider(Desc* _desc);
	~SphereCollider();

	// Collider��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:


	float m_radius;
};

