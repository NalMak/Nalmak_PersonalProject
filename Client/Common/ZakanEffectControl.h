#pragma once
#include "Component.h"
class ZakanEffectControl :
	public Component
{
public:
	struct Desc
	{

	};
public:
	ZakanEffectControl(Desc* _desc);
	~ZakanEffectControl();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override;
public:
	void CreateWeaponTrailEffect(GameObject* _weapon);
	void StartSwordTrail();
	void EndSwordTrail();
	void PlayDust();
	void PlayNATK();
	
private:
	GameObject* m_swordTrailStart;
	GameObject* m_swordTrailEnd;
	TrailRenderer* m_swordTrail;
	ParticleRenderer* m_dustParticle;
	ParticleRenderer* m_natkParticle;
	ParticleRenderer* m_splitParticle;


};


