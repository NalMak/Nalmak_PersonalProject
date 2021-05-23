#include "stdafx.h"
#include "EffectMove.h"


EffectMove::EffectMove(Desc* _desc)
{
	m_speed = _desc->speed;
	m_direction = _desc->direction;
}


EffectMove::~EffectMove()
{
}

void EffectMove::Initialize()
{
}

void EffectMove::Update()
{
	m_transform->position += m_direction *  m_speed * dTime;
}
