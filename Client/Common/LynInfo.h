#pragma once
#include "Component.h"
class LynInfo :
	public Component
{
public:
	struct Desc
	{
		float runForwardSpeed = 8.f;
		float runBackwardSpeed = 3.5f;
		float jumpPower = 6.f;
		float turningSpeed = 5.f;
		float halfHeight = 3.2f;
		float jumpHalfHeight = 0.9f;
	};
public:
	LynInfo(Desc* _desc);
	~LynInfo();
private:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	LYN_STATE m_state;

	float m_runForwardSpeed;
	float m_runBackwardSpeed;
	float m_jumpPower;
	float m_turningSpeed;
	float m_halfHeight;
	float m_jumpHalfHeight;
public:
	void EquipeWeapon(GameObject* _weapon);

private:
	GameObject* m_weapon;
};

