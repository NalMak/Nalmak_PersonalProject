#pragma once
#include "Component.h"
class LynStateControl;

class LynInfo :
	public Component
{
public:
	struct Desc
	{
		float runForwardSpeed = 14.5f;
		float runBackwardSpeed = 8.f;
		float airSpeed = 10.5f;
		float jumpPower = 16.f;
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
	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerStay(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;

	void OnCollisionEnter(Collision& _col) override;
	void OnCollisionStay(Collision& _col) override;
	void OnCollisionExit(Collision& _col) override;
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
	BitFlag<ANIMATION_FIX_PART> m_animFixPart;

public:
	float m_currentSpeed;
public:
	void EquipeWeapon(GameObject* _weapon);
	void UpdateWeapon();
private:
	GameObject* m_weapon;
	AnimationController* m_animController_lower;
	AnimationController* m_animController_upper;
	LynStateControl* m_stateControll;
	CharacterController* m_characterController;
	SkinnedMeshRenderer* m_skinRenderer;
	bool m_followingAnimationPosition;
private:
	Matrix* m_matPeaceStandard;
	Matrix* m_matBattleStandard;
	Matrix* m_matBattleHide;
private:
	Vector3 m_preAnimPos;
public:
	void SetTarget(GameObject* _obj);
	GameObject* GetTarget();
private:
	GameObject* m_target;

};

