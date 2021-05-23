#pragma once
#include "Component.h"
#include "AttackInfo.h"
class LynStateControl;
class LynSkillController;
class LynInfo :
	public Component
{
	friend class LynSkillController;
public:
	struct Desc
	{
		float runForwardSpeed = 12.5f;
		float runBackwardSpeed = 8.f;
		float sprintSpeed = 20.f;
		float airSpeed = 10.5f;
		float jumpPower = 25.f;
		float turningSpeed = 7.f;
		float halfHeight = 3.2f;
		float jumpHalfHeight = 0.9f;

		UINT power = 5000;
		UINT hp = 54600;
		float criticalRatio = 0.65f;
	};
public:
	LynInfo(Desc* _desc);
	~LynInfo();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerStay(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;

	void OnCollisionEnter(Collision& _col) override;
	void OnCollisionStay(Collision& _col) override;
	void OnCollisionExit(Collision& _col) override;
public:
	void AddLightningSpirit();
	bool UseLightningSpirit();
	bool GetDamage(UINT _damage);
	void SetState(LYN_STATE _state);
	void ChangeSkillByState(LYN_SKILL_STATE _state);

	void ResetBattleTimer();
	LYN_STATE GetState();
	void SetBattleState(BATTLE_STATE _state);
	void HitByAttackInfo(AttackInfo* _attackInfo);
	BATTLE_STATE GetBattleState();

	UINT m_power;
	float m_criticalRatio;
	float m_battleToPeaceTimer;

	float m_gravityPower;
	float m_sprintSpeed;
	float m_runForwardSpeed;
	float m_airSpeed;
	float m_runBackwardSpeed;
	float m_jumpPower;
	float m_turningSpeed;
	float m_halfHeight;
	float m_jumpHalfHeight;
	float m_currentSpeed;
private:
	UINT m_maxHp;
	UINT m_hp;
	UINT m_lightningSpirit;
	float m_energy;
	int m_innerPower;
	float m_resistanceTimer;
	bool m_resistanceAlways;
	float m_idleTimer;

public:
	void SetResistanceTimer(float _timer);
	void SetResistance(bool _resistance);
	//void SetResistanceTi(float _timer);

	float GetDistanceToTarget();
	float GetEnergy();
	void AddInnerPower(int _power);
	void ReduceInnerPower(int _power);
	int GetInnerPower();
	void PlayMoveAnimation();
	AnimationController* GetUpperAnimationController();
	AnimationController* GetLowerAnimationController();

public:
	void EquipeWeapon(GameObject* _weapon);
	void UpdateWeapon();
	void UpdateWeapon(LYN_STATE _state);
	GameObject* GetWeapon();
private:
	GameObject* m_weapon;
	AudioSource* m_sysAudio;
	AnimationController* m_animController_lower;
	AnimationController* m_animController_upper;
	LynStateControl* m_stateControl_lower;
	LynStateControl* m_stateControl_upper;

	CharacterController* m_characterController;
	SkinnedMeshRenderer* m_skinRenderer;
	LynSkillController* m_skillController;
	AudioSource* m_audio;
	bool m_followingAnimationPosition;
	bool m_isProgressSkill;
	bool m_isMovingBySkill;

public:
	Matrix* GetRightHandMatrix();
	Matrix* GetLeftHandMatrix();
private:
	Matrix* m_matPeaceStandard;
	Matrix* m_matRightHand;
	Matrix* m_matLeftHand;
private:
	Vector3 m_preAnimPos;
public:
	Vector3 GetRightHandPosition();
	bool UseEnergy(float _amount);
	void SetTarget(GameObject* _obj);
	GameObject* GetTarget();
	LYN_MOVE_DIR_STATE GetDirectionState();
private:
	GameObject* m_target;
	float m_distanceToTarget;
public:
	void StartSkill();
	void EndSkill();
	void MoveOn();
	void MoveOff();
	void SetSpeed(float _speed);
	bool IsProgressingSkill();
public:
	const  Vector3& GetTargetInput();
private:
	LYN_STATE m_state;
	BATTLE_STATE m_battleState;
	LYN_SKILL_STATE m_skillState;

	Vector3 m_inputDir;
	Vector3 m_targetInput;
	LYN_MOVE_DIR_STATE m_dirState;
	float m_targetSpeed;
	float m_innerPowerTimer;
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


};

