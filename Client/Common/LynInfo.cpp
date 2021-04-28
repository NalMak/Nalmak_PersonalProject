#include "stdafx.h"
#include "LynInfo.h"



LynInfo::LynInfo(Desc * _desc)
{
	m_runForwardSpeed = _desc->runForwardSpeed;
	m_runBackwardSpeed = _desc->runBackwardSpeed;
	m_jumpPower = _desc->jumpPower;
	m_airSpeed = _desc->airSpeed;
	m_jumpHalfHeight = _desc->jumpHalfHeight;
	m_halfHeight = _desc->halfHeight;
	m_turningSpeed = _desc->turningSpeed;
}

LynInfo::~LynInfo()
{
}

void LynInfo::Initialize()
{
	m_battleToPeaceTimer = 0;
	m_animController = GetComponent<AnimationController>();
}

void LynInfo::Update()
{
	switch (m_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		break;
	case LYN_STATE_BATTLE_STANDARD:
	{
		m_battleToPeaceTimer -= dTime;
		if (m_battleToPeaceTimer < 0.f)
		{
			m_state = LYN_STATE_PEACE_STANDARD;
			m_animController->Play("Lyn_P_BtoP_1");
		}
		break;
	}
	case LYN_STATE_BATTLE_HIDEBLADE:
	{
		m_battleToPeaceTimer -= dTime;
		if (m_battleToPeaceTimer < 0.f)
		{
			m_state = LYN_STATE_PEACE_STANDARD;
			m_animController->Play("Lyn_P_BtoP_1");

		}
		break;
	}
	default:
		break;
	}

	
}

void LynInfo::SetState(LYN_STATE _state)
{
	m_state = _state;
}

void LynInfo::EquipeWeapon(GameObject * _weapon)
{
	m_weapon = _weapon;
}
