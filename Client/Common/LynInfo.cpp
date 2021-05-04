#include "stdafx.h"
#include "LynInfo.h"
#include "LynStateControl.h"


LynInfo::LynInfo(Desc * _desc)
{
	m_runForwardSpeed = _desc->runForwardSpeed;
	m_runBackwardSpeed = _desc->runBackwardSpeed;
	m_jumpPower = _desc->jumpPower;
	m_airSpeed = _desc->airSpeed;
	m_jumpHalfHeight = _desc->jumpHalfHeight;
	m_halfHeight = _desc->halfHeight;
	m_turningSpeed = _desc->turningSpeed;

	m_currentSpeed = 0;
	m_animFixPart = 0;
	m_followingAnimationPosition = false;
}

LynInfo::~LynInfo()
{
}

void LynInfo::Initialize()
{
	m_battleToPeaceTimer = 0;
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];
	m_stateControll = GetComponent<LynStateControl>();
	m_characterController = GetComponent<CharacterController>();
	m_skinRenderer = GetComponent<SkinnedMeshRenderer>();

	m_state = LYN_STATE_PEACE_STANDARD;

	auto skin = GetComponent<SkinnedMeshRenderer>();
	m_matBattleStandard = skin->GetBoneCombinedMatrix("WeaponR");
	m_matBattleHide = skin->GetBoneCombinedMatrix("WeaponL");
	m_matPeaceStandard = skin->GetBoneCombinedMatrix("Bip01Spine2");

}

void LynInfo::Update()
{
	//if (m_followingAnimationPosition)
	//{
	//	Matrix* boneMat = m_skinRenderer->GetBoneCombinedMatrix("Bip01Spine2");
	//	Matrix worldMat = m_transform->GetWorldMatrix();
	//	/*	worldMat._41 = m_recordedPos.x;
	//		worldMat._42 = m_recordedPos.x;
	//		worldMat._43 = m_recordedPos.x;*/
	//	Vector3 movePos = Vector3(boneMat->_41, boneMat->_42, boneMat->_43);
	//	D3DXVec3TransformNormal(&movePos, &movePos, &worldMat);
	//	m_characterController->SetFootPosition(m_recordedPos);
	//}
	//else
	//{

	//}
	//m_characterController->SetVelocity(0, 0, 0);
	//
	//DEBUG_LOG(L"root pos", Vector3(worldMat->_41, worldMat->_42, worldMat->_43));
}

void LynInfo::OnTriggerEnter(Collision & _col)
{
	DEBUG_LOG(L"Lyn Trigger!", L"enter");

}

void LynInfo::OnTriggerStay(Collision & _col)
{
}

void LynInfo::OnTriggerExit(Collision & _col)
{
	DEBUG_LOG(L"Lyn Trigger!", L"exit");
}

void LynInfo::OnCollisionEnter(Collision & _col)
{
}

void LynInfo::OnCollisionStay(Collision & _col)
{
	DEBUG_LOG(L"Lyn Collision!" , L"stay");
}

void LynInfo::OnCollisionExit(Collision & _col)
{
}

void LynInfo::SetState(LYN_STATE _state)
{
	switch (_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		m_battleToPeaceTimer = 0.f;
		break;
	case LYN_STATE_BATTLE_STANDARD:
		m_battleToPeaceTimer = 5.f;
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		m_battleToPeaceTimer = 5.f;
		break;
	default:
		break;
	}
	
	m_state = _state;
}


void LynInfo::EquipeWeapon(GameObject * _weapon)
{
	m_weapon = _weapon;
}

void LynInfo::UpdateWeapon()
{
	switch (m_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		m_weapon->SetParents(m_transform, m_matPeaceStandard);
		m_weapon->SetRotation(0, 0, 65);
		m_weapon->SetPosition(7, -4.5f, -4.f);
		break;
	case LYN_STATE_BATTLE_STANDARD:
		m_weapon->SetParents(m_transform, m_matBattleStandard);
		m_weapon->SetRotation(0, 0, 0);
		m_weapon->SetPosition(0, 0, 0);
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		m_weapon->SetParents(m_transform, m_matBattleHide);
		break;
	default:
		break;
	}

}

void LynInfo::SetTarget(GameObject * _obj)
{
	m_target = _obj;
}

GameObject * LynInfo::GetTarget()
{
	return m_target;
}
