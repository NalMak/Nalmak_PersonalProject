#include "..\Include\Component.h"

USING(Nalmak)
#include "Transform.h"
Component::Component()
{
	m_isActive = true;
	m_isDead = false;
	m_name = "default";
}


Component::~Component()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::LateUpdate()
{
}

void Component::Release()
{
}

void Component::PreRender()
{
}

void Component::EachRender()
{
}

void Component::PostRender()
{
}

void Component::OnTriggerEnter(Collision & _col)
{
}

void Component::OnTriggerStay(Collision & _col)
{
}

void Component::OnTriggerExit(Collision & _col)
{
}

void Component::OnCollisionEnter(Collision & _col)
{
}

void Component::OnCollisionStay(Collision & _col)
{
}

void Component::OnCollisionExit(Collision & _col)
{
}


void Component::SetActive(bool _active)
{
	m_isActive = _active;
	if (m_isActive)
		OnEnable();
	else
		OnDisable();

}

bool Component::IsActive()
{
	if (m_gameObject->IsActive())
		return m_isActive;
	else
		return false;
}

bool Component::IsAlive()
{
	return !m_isDead;
}

void Component::SetPosition(const Vector3 & _pos)
{
	m_transform->position = _pos;
}

void Component::SetPosition(float _x, float _y, float _z)
{
	m_transform->position = { _x,_y,_z };
}

void Component::SetScale(const Vector3 & _scale)
{
	m_transform->scale = _scale;
}

void Component::SetScale(float _x, float _y, float _z)
{
	m_transform->scale = { _x,_y,_z };
}
