#pragma once
#include "Collider.h"
class NALMAK_DLL BoxCollider : public Collider
{
public:
	struct Desc
	{
		float width = 1;
		float height = 1;
		float depth = 1;
		bool isTrigger = false;
	};
public:
	BoxCollider(Desc* _desc);
	~BoxCollider();

	// Collider을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_width;
	float m_height;
	float m_depth;
};

