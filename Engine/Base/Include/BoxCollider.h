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
		Vector3 posOffset = { 0,0,0 };
		bool isTrigger = false;
	};
public:
	BoxCollider(Desc* _desc);
	~BoxCollider();

	// Collider을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	float GetWidht() { return m_width; }
	float GetHeight() { return m_height; }
	float GetDepth() { return m_depth; }

	void SetWidth(float _value);
	void SetHeight(float _value);
	void SetDepth(float _value);
private:
	float m_width;
	float m_height;
	float m_depth;

};



