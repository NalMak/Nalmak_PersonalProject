#pragma once

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Nalmak_Include.h"
class Transform;
class Particle
{
public:
	Particle();
	~Particle();
public:
	Vector3 position = Vector3(0, 0, 0);
	Vector3 totalAcceleration = Vector3(0, 0, 0); // 누적 가속
	Vector3 direction = Vector3(0, 1, 0);
	Vector3 acceleration = Vector3(0, 0, 0);
	float startSpeed = 0.f;
	float endSpeed = 0.f;
	float angle = 0.f;
	float angluarVelocity = 0.f;
	float startScale = 1.f;
	float endScale = 0.f;
	Vector4 startColor = Vector4(1, 1, 1, 1);
	Vector4 endColor = Vector4(1, 1, 1, 0);
	float lifeTime = 3.f;
	float gravityScale = 0.f;
	Transform* parents = nullptr;
	float StretchedScale = 2.f;
private:
	float m_currentLifeTime = 0.f;
	bool m_isAlive;
public:
	void Reset();
	bool IsAlive() { return m_isAlive; }
	void Update(INPUT_LAYOUT_PARTICLE* _info, const Matrix& _billboard,float _spriteCountRatio, PARTICLE_BILLBOARD_TYPE _type);
};

#endif
