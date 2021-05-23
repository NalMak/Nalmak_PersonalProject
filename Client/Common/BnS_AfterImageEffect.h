#pragma once
#include "Component.h"
class BnS_AfterImageEffect :
	public Component
{
public:
	struct Desc
	{
		GameObject* object = nullptr;
		float lifeTime = 1;
		Vector4 color = { 1,1,1,1};
	};
public:
	BnS_AfterImageEffect(Desc* _desc);
	~BnS_AfterImageEffect();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;

private:
	Vector4 m_color;
	float m_lifeTime;
	Material* m_effectMaterial;
	GameObject* m_originObj;
};

