#pragma once
#include "Component.h"
class LynInfo :
	public Component
{
public:
	struct Desc
	{
		float runForwardSpeed = 14.f;
		float runBackwardSpeed = 6.5f;
		float airSpeed = 10.5f;
		float jumpPower = 15.f;
		float turningSpeed = 7.f;
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
	void SetState(LYN_STATE _state);
	LYN_STATE m_state;
	float m_battleToPeaceTimer;

	float m_runForwardSpeed;
	float m_airSpeed;
	float m_runBackwardSpeed;
	float m_jumpPower;
	float m_turningSpeed;
	float m_halfHeight;
	float m_jumpHalfHeight;
public:
	void EquipeWeapon(GameObject* _weapon);

private:
	GameObject* m_weapon;
	AnimationController* m_animController;
};

