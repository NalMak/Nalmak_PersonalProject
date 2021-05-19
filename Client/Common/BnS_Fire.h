#pragma once
#include "Component.h"
class BnS_Fire :
	public Component
{
public:
	struct Desc
	{

	};
public:
	BnS_Fire(Desc* _desc);
	~BnS_Fire();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	GameObject* m_fireImage[6];
	PointLight* m_pointLight;

	float m_lightRadiusTimer;
	float m_lightTargetTime;
};

