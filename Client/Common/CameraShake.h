#pragma once
#include "Component.h"
class CameraShake :
	public Component
{
public:
	struct Desc
	{
	};
public:
	CameraShake(Desc* _desc);
	~CameraShake();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	Vector3 m_targetPos;
	Vector3 m_originPos;

	Vector3 m_direction;
	//float m_angle;
	float m_timer;
	float m_interval;
	int m_count;
	float m_minPower;
	float m_maxPower;
	float m_followSpeed;
public:
	void Shake(float _minPower,float _maxPower, int _count, float _interval, float _followSpeed,Vector3 _direction = { 0,0,0 });
};

