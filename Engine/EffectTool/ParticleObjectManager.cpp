#include "stdafx.h"
#include "ParticleObjectManager.h"

IMPLEMENT_SINGLETON(ParticleObjectManager)

ParticleObjectManager::ParticleObjectManager()
{
}


ParticleObjectManager::~ParticleObjectManager()
{
}

void ParticleObjectManager::AddObject(GameObject * _obj)
{
	m_particleObject.emplace_back(_obj);
}

void ParticleObjectManager::DeleteObject(int _index)
{
	if (m_particleObject.size() > _index)
	{
		DESTROY(*(m_particleObject.begin() + _index));
		m_particleObject.erase(m_particleObject.begin() + _index);
	}
}

GameObject * ParticleObjectManager::GetParticleObject(int _index)
{
	if (_index < m_particleObject.size())
		return m_particleObject[_index];
	return nullptr;
}

void ParticleObjectManager::OnActiveParticle(int _index)
{
	if (_index < m_particleObject.size())
		m_particleObject[_index]->GetComponent<ParticleRenderer>()->Play();
}

void ParticleObjectManager::OnActiveParticle(GameObject * _obj)
{
	for (auto& particle : m_particleObject)
	{
		if (particle == _obj)
		{
			particle->GetComponent<ParticleRenderer>()->Play();
			return;
		}
	}
}

void ParticleObjectManager::OnActiveParticles()
{
	for (auto& particle : m_particleObject)
	{
		particle->GetComponent<ParticleRenderer>()->Play();
	}
}

void ParticleObjectManager::OffActiveParticles()
{
	for (auto& particle : m_particleObject)
	{
		particle->GetComponent<ParticleRenderer>()->Stop();
	}
}
