#pragma once

#ifndef __PARTICLE_RENDERER_H__
#define __PARTICLE_RENDERER_H__
#include "IRenderer.h"
#include "DynamicInstanceBuffer.h"
class Particle;

class NALMAK_DLL ParticleRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		bool PlayOnAwake = true;
		wstring particleDataName = L"default";
	};

	struct Burst
	{
		float time;
		UINT count;
	};
	ParticleRenderer(Desc* _desc);
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render(Shader* _shader) override;
private:
	virtual void BindingStreamSource();
public:
	// IRenderer��(��) ���� ��ӵ�
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) override;
private:
	VIBuffer* m_viBuffer;
	Material* m_material;
public:
	// ��Ÿ���߿� �ظ��ؼ� �ٲ�������! ����� ���ſ� �۾�
	void UpdateParticleInfo(int _maxCount);

	void SetGravityScale(float _scale);
public:
	ParticleData m_info;
private:
	float m_awakeTime = 0;
	float m_playTime = 0;
	float m_currentEmitTime;
	int m_currentCount;
	float m_secPerEmit;
public:
	void Emit(int _count, const Matrix& _world);
	void SetEmitCount(int _count);
private:
	void EmitSphere(int _count, const Matrix& _world);
	void EmitCircle(int _count, const Matrix& _world);
	void EmitBox(int _count, const Matrix& _world);
	void EmitCone(int _count, const Matrix& _world);
public:
	void Stop();
	void StopEmit();
	void Play();
	bool IsPlaying();

public:
	const vector<Burst>& GetBurstList() { return m_emitBursts; }
	void AddBurst(Burst _burst);
	void DeleteBurst(size_t _index);
	void SetAnimationCount(int _count);
	size_t GetActivedParticleCount();

private:
	list<Particle*> m_activedParticles;
	queue<Particle*> m_particlePool;
	INPUT_LAYOUT_PARTICLE* m_particlesInfo;
	vector<Burst> m_emitBursts;
	size_t m_currentBurstIndex;
	size_t m_currentBurstTime;

	Burst* m_currentBurst;
	float m_spriteIndexRatio;
	class Camera* m_camera;
private:
	DynamicInstanceBuffer<INPUT_LAYOUT_PARTICLE> * m_instanceBuffer;
	void ParticleUpdate();




};

#endif
