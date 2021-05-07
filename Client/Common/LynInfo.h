#pragma once
#include "Component.h"
class LynStateControl;
class LynSkillController;

class LynInfo :
	public Component
{
	friend class LynSkillController;
public:
	struct Desc
	{
		float runForwardSpeed = 14.5f;
		float runBackwardSpeed = 8.f;
		float airSpeed = 10.5f;
		float jumpPower = 25.f;
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
	LYN_STATE GetState();

	float m_battleToPeaceTimer;

	float m_runForwardSpeed;
	float m_airSpeed;
	float m_runBackwardSpeed;
	float m_jumpPower;
	float m_turningSpeed;
	float m_halfHeight;
	float m_jumpHalfHeight;
	float m_currentSpeed;
private:
	UINT m_energy;
public:
	UINT GetEnergy();
public:
	void EquipeWeapon(GameObject* _weapon);
	void UpdateWeapon();
	void UpdateWeapon(LYN_STATE _state);

private:
	GameObject* m_weapon;
	AnimationController* m_animController_lower;
	AnimationController* m_animController_upper;
	LynStateControl* m_stateControl_lower;
	LynStateControl* m_stateControl_upper;

	CharacterController* m_characterController;
	SkinnedMeshRenderer* m_skinRenderer;
	LynSkillController* m_skillController;
	bool m_followingAnimationPosition;
	bool m_isProgressSkill;
private:
	Matrix* m_matPeaceStandard;
	Matrix* m_matBattleStandard;
	Matrix* m_matBattleHide;
private:
	Vector3 m_preAnimPos;
public:
	void SetTarget(GameObject* _obj);
	GameObject* GetTarget();
	LYN_MOVE_DIR_STATE GetDirectionState();
private:
	GameObject* m_target;
public:
	void StartSkill();
	void EndSkill();
	void SetSpeed(float _speed);
private:
	LYN_STATE m_state;

	Vector3 m_inputDir;
	Vector3 m_targetInput;
	LYN_MOVE_DIR_STATE m_dirState;
	float m_targetSpeed;
	Vector3 m_directionState[9] = {
		{ 0, 0, 1 },
		{ 1,0,0 },
		Nalmak_Math::Normalize({ 1,0,1 }),
		{ -1,0,0 },
		Nalmak_Math::Normalize({ -1,0,1 }),
		{ 0,0,-1 },
		Nalmak_Math::Normalize({ 1,0,-1 }),
		Nalmak_Math::Normalize({ -1,0,-1 }),
		{ 0,0,0 }
	};

private:
	float m_sKeyTimer;
};

