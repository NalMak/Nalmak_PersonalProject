#include "stdafx.h"
#include "Homework_Player.h"


Homework_Player::Homework_Player(Desc * _desc)
{
}

Homework_Player::~Homework_Player()
{
}

void Homework_Player::Initialize()
{
	m_yAxisAngle = 0.f;
	
}

void Homework_Player::Update()
{
	m_yAxisAngle += dTime * 5;
	m_transform->SetRotationY(m_yAxisAngle);
}
