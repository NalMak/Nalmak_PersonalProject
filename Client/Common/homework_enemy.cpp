#include "stdafx.h"
#include "homework_enemy.h"
#include "Homework_Player.h"





homework_enemy::homework_enemy(Desc * _Desc)
{
	m_player = _Desc->target->GetComponent<Homework_Player>();
}

homework_enemy::~homework_enemy()
{
}

void homework_enemy::Initialize()
{
}

void homework_enemy::Update()
{
	m_transform->rotation = m_player->GetTransform()->rotation;
	
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_player->GetTransform()->GetWorldPosition(), dTime * 2);
	
}
