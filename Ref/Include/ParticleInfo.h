#pragma once
#include "IResource.h"
#include "ParticleRenderer.h"

class ParticleInfo :
	public IResource
{
public:
	ParticleInfo();
	~ParticleInfo();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
private:
	ParticleData m_info;
	vector<ParticleRenderer::Burst> m_bursts;
	Material* m_material;
public:

	const ParticleData& GetParticleInfo() { return m_info; }
	vector<ParticleRenderer::Burst> GetParticleBurst() { return m_bursts; }
	Material* GetMaterial() { return m_material; }
};

