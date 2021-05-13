#pragma once
#include "IResource.h"

struct NALMAK_DLL ParticleData
{
public:
	struct Burst
	{
		float time;
		UINT count;
	};

	Vector3 posOffset;
	Quaternion rotOffset;

	PARTICLE_EMIT_SHAPE shape = PARTICLE_EMIT_SHAPE::PARTICLE_EMIT_SHAPE_SPHERE;
	PARTICLE_BILLBOARD_TYPE billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_DEFAULT;
	// for Circle
	// for Sphere 
	float minRadius = 0.2f;
	float maxRadius = 0.3f;

	// for box
	float width = 1.f;
	float height = 1.f;
	float depth = 1.f;

	// for cone
	float coneAngle = 45.f * Deg2Rad;

	float startMinSpeed = 0.1f;
	float startMaxSpeed = 0.1f;
	float endMinSpeed = 0.1f;
	float endMaxSpeed = 0.15f;

	UINT emittorCount = 30;
	float duration = 5.f;
	float minAwakeTime = 0.f;
	float maxAwakeTime = 0.f;


	Vector3 force = Vector3(0, 0, 0);

	float gravity = 0.f;

	float minAngle = 0.f;
	float maxAngle = 0.f;

	float minAngularVelocity = 0.f;
	float maxAngularVelocity = 0.f;

	float startMinScale = 0.1f;
	float startMaxScale = 0.2f;
	float endMinScale = 0.15f;
	float endMaxScale = 0.2f;


	Vector4 startMinColor = Vector4(1, 1, 1, 1);
	Vector4 startMaxColor = Vector4(1, 1, 1, 1);
	Vector4 endMinColor = Vector4(0, 0, 0, 0);
	Vector4 endMaxColor = Vector4(0, 0, 0, 0);

	float minLifeTime = 3;
	float maxLifeTime = 5;

	float stretchedScale = 2.f;
	int animationTileX = 1;
	int animationTileY = 1;

	int maxParticleCount = 300;

	bool  isLoop = true;
	bool  isPlay = true;
	bool isPlayOnAwake = true;
	bool isLocal = false;
	bool isVelocityLocal = false;
};

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
	vector<ParticleData::Burst> m_bursts;
	class Material* m_material;
public:
	const ParticleData& GetParticleInfo() { return m_info; }
	vector<ParticleData::Burst> GetParticleBurst() { return m_bursts; }
	class Material* GetMaterial() { return m_material; }
};

