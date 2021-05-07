#include "stdafx.h"
#include "LynInfo.h"
#include "LynStateControl.h"
#include "LynSkillController.h"
#include "UIManager.h"

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
	
	m_followingAnimationPosition = false;
}

LynInfo::~LynInfo()
{
}

void LynInfo::Initialize()
{
	m_energy = 100;
	m_sKeyTimer = 0.f;
	m_battleToPeaceTimer = 0;
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];
	m_stateControl_lower = GetComponents<LynStateControl>()[0];
	m_stateControl_upper = GetComponents<LynStateControl>()[1];
	m_characterController = GetComponent<CharacterController>();
	m_skinRenderer = GetComponent<SkinnedMeshRenderer>();
	m_skillController = GetComponent<LynSkillController>();

	auto skin = GetComponent<SkinnedMeshRenderer>();
	m_matBattleStandard = skin->GetBoneCombinedMatrix("WeaponR");
	m_matBattleHide = skin->GetBoneCombinedMatrix("WeaponL");
	m_matPeaceStandard = skin->GetBoneCombinedMatrix("Bip01Spine2");


	m_state = LYN_STATE_PEACE_STANDARD;
	UpdateWeapon();
}

void LynInfo::Update()
{
	m_targetInput = { 0,0,0 };
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_targetInput += {0, 0, 1};
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_targetInput -= {0, 0, 1};
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_targetInput -= {1, 0, 0};
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_targetInput += {1, 0, 0};
	}
	m_targetInput = Nalmak_Math::Normalize(m_targetInput);

	m_inputDir = Nalmak_Math::Lerp(m_inputDir, m_targetInput, dTime * 10);

	float shortLength = INFINITY;
	int index = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (m_targetInput != Vector3(0, 0, 0))
		{
			if(i == LYN_MOVE_DIR_STATE_NONE)
				continue;
		}
		float length = Nalmak_Math::DistanceSq(m_directionState[i], m_inputDir);
		if (length < shortLength)
		{
			index = i;
			shortLength = length;
		}
	}
	m_dirState = (LYN_MOVE_DIR_STATE)index;
	Vector3 velocity = { 0,0,0 };

	float speedRatio = 1.f;
	switch (m_state)
	{
	case LYN_STATE_PEACE_STANDARD:
		speedRatio = 1.f;
		break;
	case LYN_STATE_BATTLE_STANDARD:
		speedRatio = 1.1f;
		break;
	case LYN_STATE_BATTLE_HIDEBLADE:
		speedRatio = 1.15f;
		break;
	default:
		break;
	}
	velocity += m_inputDir.x * m_transform->GetRight() * m_targetSpeed * speedRatio;
	velocity += m_inputDir.z * m_transform->GetForward() * m_targetSpeed * speedRatio;

	m_characterController->SetVelocityX(velocity.x);
	m_characterController->SetVelocityZ(velocity.z);
	
	if (!m_characterController->IsGround())
	{
		m_characterController->AddVelocity(0, -60 * dTime, 0);
	}

	if (m_state != LYN_STATE_PEACE_STANDARD)
	{
		m_battleToPeaceTimer -= dTime;
		if (m_battleToPeaceTimer <= 0.f)
		{
			m_battleToPeaceTimer = INFINITY;
			
			m_stateControl_upper->SetInteger(L"IsBlend", 1);
			m_stateControl_upper->SetState(L"battleToPeace");
			return;
		}
	}
	if (m_isProgressSkill)
		return;

	/*if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		m_stateControl_upper->SetState(L"test");
		m_stateControl_lower->SetState(L"test");
	}*/

	m_skillController->ActiveSkill();

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
		m_sKeyTimer = 0.5f;
	m_sKeyTimer -= dTime;
}

void LynInfo::OnTriggerEnter(Collision & _col)
{

}

void LynInfo::OnTriggerStay(Collision & _col)
{
}

void LynInfo::OnTriggerExit(Collision & _col)
{
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
		m_battleToPeaceTimer =INFINITY;
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
	UpdateWeapon();
	m_state = _state;
}

LYN_STATE LynInfo::GetState()
{
	return m_state;
}



UINT LynInfo::GetEnergy()
{
	return m_energy;
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
		m_weapon->SetRotation(0, 0, 0);
		m_weapon->SetPosition(0.f, 0.f, 0);
		break;
	default:
		break;
	}

}

void LynInfo::UpdateWeapon(LYN_STATE _state)
{
	switch (_state)
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
		m_weapon->SetRotation(0, 0, 0);
		m_weapon->SetPosition(0.f, 0.f, 0);
		break;
	default:
		break;
	}
}

bool LynInfo::UseEnergy(float _amount)
{
	if (m_energy >= 0)
	{
		m_energy += dTime * _amount;
		UIManager::GetInstance()->UpdateEnergyUI(m_energy / 100.f);
		return true;
	}
	else
	{
		m_energy = 0;
		return false;
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

LYN_MOVE_DIR_STATE LynInfo::GetDirectionState()
{
	return m_dirState;
}

void LynInfo::StartSkill()
{
	m_isProgressSkill = true;
	m_battleToPeaceTimer = 5.f;
}

void LynInfo::EndSkill()
{
	m_isProgressSkill = false;
}

void LynInfo::SetSpeed(float _speed)
{
	m_targetSpeed = _speed;
}
