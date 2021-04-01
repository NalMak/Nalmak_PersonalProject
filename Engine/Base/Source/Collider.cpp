#include "Collider.h"



Collider::Collider(bool _isTrigger,const Vector3& _posOffset)
{
	m_offset = _posOffset;
	m_isTrigger = _isTrigger;
}


Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
}
