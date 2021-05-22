#pragma once
#include "Component.h"
class ZakanFloorAttack :
	public Component
{
public:
	struct Desc
	{
		GameObject* host;
	};
public:
	ZakanFloorAttack(Desc* desc);
	~ZakanFloorAttack();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;
private:
	void Explosion();
private:
	GameObject* m_host;
	Material* m_material;
	float m_explosionTimer;
	float m_floatSpeed;
	float m_currentUV_X;
};

