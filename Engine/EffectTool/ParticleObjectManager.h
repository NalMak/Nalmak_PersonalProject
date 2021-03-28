#pragma once
#include "Core.h"
#include "Nalmak_Include.h"
class ParticleObjectManager
{
	DECLARE_SINGLETON(ParticleObjectManager)
private:
	ParticleObjectManager();
	~ParticleObjectManager();
public:
	void AddObject(GameObject* _obj);
	void DeleteObject(int _index);
	GameObject* GetParticleObject(int _index);
	vector<GameObject*>& GetAllObjects() { return m_particleObject; }
	void OnActiveParticle(int _index);
	void OnActiveParticle(GameObject* _obj);

	void OnActiveParticles();
	void OffActiveParticles();
private:
	vector<GameObject*> m_particleObject;
};

