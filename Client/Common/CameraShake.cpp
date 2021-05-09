#include "stdafx.h"
#include "CameraShake.h"


CameraShake::CameraShake(Desc * _desc)
{
}

CameraShake::~CameraShake()
{
}

void CameraShake::Initialize()
{
}

void CameraShake::Update()
{
	if (m_count == 0)
	{
		m_transform->position = m_originPos;
		SetActive(false);
		return;
	}

	m_timer += dTime;

	if (m_timer >= m_interval)
	{
		--m_count;
		m_timer -= m_interval;

		if (m_count % 2 == 0)
		{
			m_targetPos = m_originPos;
			m_transform->position = m_originPos;
		}
		else
		{
			m_targetPos = m_originPos + Nalmak_Math::Rand(m_minPower, m_maxPower) * m_direction;
		}
	}
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_transform->position + m_targetPos, dTime * m_followSpeed);

}

void CameraShake::Shake(float _minPower, float _maxPower, int _count, float _interval, float _followSpeed,Vector3 _direction)
{
	SetActive(true);

	m_originPos = m_transform->position;
	m_minPower = _minPower;
	m_maxPower = _maxPower;
	m_count = _count;
	m_interval = _interval;
	m_followSpeed = _followSpeed;
	m_targetPos = m_originPos + Nalmak_Math::Rand(m_minPower, m_maxPower) * m_direction;
	m_direction = Nalmak_Math::Normalize(_direction);
}

