#pragma once
#include "Component.h"
class LynWeapon;
class LynInfo;

class LynEffectControl :
	public Component
{
public:
	struct Desc
	{

	};
public:
	LynEffectControl(Desc* _desc);
	~LynEffectControl();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	void StartWeaponTrail();
	void EndWeaponTrail();
	void StartBodyTrail();
	void EndBodyTrail();

	void PlayBaldoEffect();
	void PlayLightningComboEffect();
private:
	LynInfo* m_info;
	LynWeapon* m_weaponTrail;
	bool m_bodyTrail;

	GameObject* m_leftHandPos;
	GameObject* m_rightHandPos;

	TrailRenderer* m_leftHandTrail;
	TrailRenderer* m_rightHandTrail;

	ParticleRenderer* m_baldoParticle;
	ParticleRenderer* m_lightningComboParticle;
};

