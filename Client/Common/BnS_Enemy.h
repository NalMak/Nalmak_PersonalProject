#pragma once
#include "Component.h"
#include "AttackInfo.h"
class EnemyStateControl;

class BnS_Enemy :
	public Component
{
public:
	struct Desc
	{
		UINT hp = 3000000;
		float hitRadius = 3.f;
		UINT power = 1500;
		float detectionRadius = 10.f;
		Vector4 volumeRect = { 6,9,6,4.5f};
	};
public:
	BnS_Enemy(Desc* _desc);
	~BnS_Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	
	void OnTriggerEnter(Collision& _col) override;
	void OnTriggerExit(Collision& _col) override;
public:
	void HitByAttackInfo(AttackInfo* _attack);
	
public:
	BATTLE_STATE GetBattleState();
	void SetBattleState(BATTLE_STATE _state);

	const Vector3& GetSpawnPos();
	const Quaternion& GetSpawnRot();
	const Vector4& GetVolume();
	const RECT& GetScreenVolume();

	GameObject* GetTarget();
	float GetDistanceToTarget();
	void LostTarget();
	void LookTarget();
	void GetDamage(AttackInfo* _attackInfo);
	float GetHpRatio();
	void Reset();
private:
	Vector4 m_volumeRect;
	RECT m_screenVolumeRect;
	int m_maxHp;
	int m_hp;
	UINT m_power;
	float m_hitRadius;
	Vector3 m_spawnPos;
	Quaternion m_spawnRot;
	BATTLE_STATE m_battleState;
	bool m_isAggro;
	float m_detectionRadius;
	GameObject* m_target;
	float m_distanceToTarget;
	CharacterController* m_character;
	EnemyStateControl* m_stateControl;
	AudioSource* m_audio;
	ParticleRenderer* m_defaultParticle;
private:
	void CalcWorldVolume();
};

