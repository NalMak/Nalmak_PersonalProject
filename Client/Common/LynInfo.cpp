#include "stdafx.h"
#include "LynInfo.h"
#include "LynStateControl.h"
#include "LynSkillController.h"
#include "UIManager.h"
#include "BnS_Enemy.h"

LynInfo::LynInfo(Desc * _desc)
{
	m_runForwardSpeed = _desc->runForwardSpeed;
	m_runBackwardSpeed = _desc->runBackwardSpeed;
	m_jumpPower = _desc->jumpPower;
	m_airSpeed = _desc->airSpeed;
	m_jumpHalfHeight = _desc->jumpHalfHeight;
	m_halfHeight = _desc->halfHeight;
	m_turningSpeed = _desc->turningSpeed;
	m_criticalRatio = _desc->criticalRatio;
	m_power = _desc->power;

	m_currentSpeed = 0;
	m_innerPowerTimer = 0;
	m_innerPower = 10;

	m_followingAnimationPosition = false;

	m_hp = _desc->hp;
	m_maxHp	 = _desc->hp;
}

LynInfo::~LynInfo()
{
}

void LynInfo::Initialize()
{
	m_lightningSpirit = 0;
	m_energy = 100;
	m_sKeyTimer = 0.f;
	m_battleToPeaceTimer = 0.f;
	m_resistanceTimer = 0.f;
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];
	m_stateControl_lower = GetComponents<LynStateControl>()[0];
	m_stateControl_upper = GetComponents<LynStateControl>()[1];
	m_characterController = GetComponent<CharacterController>();
	m_skinRenderer = GetComponent<SkinnedMeshRenderer>();
	m_skillController = GetComponent<LynSkillController>();
	m_sysAudio = Core::GetInstance()->GetMainCamera()->GetComponent<AudioSource>();


	auto skin = GetComponent<SkinnedMeshRenderer>();
	m_matBattleStandard = skin->GetBoneCombinedMatrix("WeaponR");
	m_matBattleHide = skin->GetBoneCombinedMatrix("WeaponL");
	m_matPeaceStandard = skin->GetBoneCombinedMatrix("Bip01Spine2");


	m_state = LYN_STATE_PEACE_STANDARD;
	m_battleState = BATTLE_STATE_WEAK;

	UpdateWeapon();

	m_idleTimer = 0.f;
}

void LynInfo::Update()
{
	DEBUG_LOG(L"Battle State", m_battleState);




	if (m_stateControl_lower->GetCurStateString() == L"idle" && m_stateControl_upper->GetCurStateString() == L"idle")
	{
		if (m_idleTimer > 4.f)
		{
			m_stateControl_lower->SetState(L"eventIdle");
			m_stateControl_upper->SetState(L"eventIdle");
			return;
		}
		else
		{
			m_idleTimer += dTime;
		}
	}
	else
	{
		m_idleTimer = 0;
	}

	if (m_resistanceAlways)
		m_battleState = BATTLE_STATE_RESISTANCE;

	if (m_resistanceTimer > 0.f)
	{
		m_resistanceTimer -= dTime;
		m_battleState = BATTLE_STATE_RESISTANCE;
		if (m_resistanceTimer <= 0.f)
		{
			m_battleState = BATTLE_STATE_WEAK;
		}
	}

	


	if (m_state == LYN_STATE_PEACE_STANDARD)
	{
		if (m_innerPower < 10) // 자동 내력 충전
		{
			m_innerPowerTimer += dTime;

			if (m_innerPowerTimer > 2.f)
			{
				m_innerPowerTimer = 0;
				AddInnerPower(1);
			}
		}
	}

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

	if (!m_isMovingBySkill)
	{
		float shortLength = INFINITY;
		int index = 0;
		for (int i = 0; i < 9; ++i)
		{
			if (m_targetInput != Vector3(0, 0, 0))
			{
				if (i == LYN_MOVE_DIR_STATE_NONE)
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
		
	}
	
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
			
			m_stateControl_upper->SetState(L"battleToPeace");
			return;
		}
	}


	if (m_target)
	{
		if (m_target->GetComponent<BnS_Enemy>()->GetBattleState() == BATTLE_STATE_DOWN)
		{
			if(InputManager::GetInstance()->GetKeyDown(KEY_STATE_F))
			{
				m_stateControl_lower->SetState(L"upperSlash");
				m_stateControl_upper->SetState(L"upperSlash");
				return;
			}
		}
	}
	//Nalmak_Math::Random<wstring>(L"1", L"2", L"3");
	

	
}

void LynInfo::LateUpdate()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
	{
		m_sKeyTimer = 0.3f;
	}
	m_sKeyTimer -= dTime;
}

void LynInfo::OnTriggerEnter(Collision & _col)
{

	if (_col.hitObj->GetTag() == OBJECT_TAG_ATTACKINFO)
	{
		if (_col.hitObj->GetLayer() == OBJECT_LAYER_ENEMY_HITBOX)
		{
			AttackInfo* attack = _col.hitObj->GetComponent<AttackInfo>();
			auto attackType = attack->m_attackType;
			ResetBattleTimer();

			if (m_battleState == BATTLE_STATE_RESISTANCE)
			{
				m_sysAudio->PlayOneShot(L"lyn_resistance");
				return;
			}
			if (!GetDamage(attack->m_power))
			{
				attack->GetHost()->GetComponent<BnS_Enemy>()->LostTarget();
				return;
			}
			
			if (m_battleState == BATTLE_STATE_WEAK)
			{
				switch (attackType)
				{
				case ATTACK_TYPE_DOWN:
					m_stateControl_lower->SetFloat(L"downTime", attack->m_ccTime);
					m_stateControl_upper->SetFloat(L"downTime", attack->m_ccTime);

					m_stateControl_lower->SetState(L"down");
					m_stateControl_upper->SetState(L"down");
					break;
				case ATTACK_TYPE_GROGY:
					m_stateControl_lower->SetFloat(L"grogyTime", attack->m_ccTime);
					m_stateControl_upper->SetFloat(L"grogyTime", attack->m_ccTime);

					m_stateControl_lower->SetState(L"grogy");
					m_stateControl_upper->SetState(L"grogy");
					break;
				case ATTACK_TYPE_MAGNETIC:
					
					m_stateControl_lower->SetState(L"hold");
					m_stateControl_upper->SetState(L"hold");
				default:
					break;
				}
			}
		}
	}


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

void LynInfo::AddLightningSpirit()
{
	if (m_lightningSpirit < 3)
	{
		++m_lightningSpirit;
	}
}

bool LynInfo::UseLightningSpirit()
{
	if (m_lightningSpirit > 0)
	{
		--m_lightningSpirit;
		return true;
	}
	return false;
}

bool LynInfo::GetDamage(UINT _damage)
{
	if (m_hp > _damage)
	{
		m_hp -= _damage;
		UIManager::GetInstance()->UpdateHpUI((float)m_hp / m_maxHp);
		return true;
	}
	else
	{
		UIManager::GetInstance()->UpdateHpUI(0);
		m_stateControl_upper->SetState(L"dead");
		m_stateControl_lower->SetState(L"dead");
		return false;
	}
}

void LynInfo::SetState(LYN_STATE _state)
{
	switch (_state)
	{
	case LYN_STATE_PEACE_STANDARD:
	{
		m_battleToPeaceTimer = INFINITY;
		m_innerPowerTimer = 0;
		break;
	}
	case LYN_STATE_BATTLE_STANDARD:
	{
		m_battleToPeaceTimer = BNS_BATTLE_TO_PEACE_TIME;
		break;
	}
	case LYN_STATE_BATTLE_HIDEBLADE:
	{
		m_battleToPeaceTimer = BNS_BATTLE_TO_PEACE_TIME;
		break;
	}
	default:
		break;
	}


	if (m_state != _state)
	{
		if (_state == LYN_STATE_BATTLE_HIDEBLADE)
		{
			ChangeSkillByState(LYN_SKILL_STATE_HIDE);
		}
		else if (_state == LYN_STATE_BATTLE_STANDARD)
		{
			ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
		}
		else if (_state == LYN_STATE_PEACE_STANDARD)
		{
			if(m_state == LYN_STATE_BATTLE_HIDEBLADE)
				ChangeSkillByState(LYN_SKILL_STATE_STANDARD);
		}

		m_state = _state;
		UpdateWeapon();
	}
}



void LynInfo::ChangeSkillByState(LYN_SKILL_STATE _state)
{
	switch (_state)
	{
	case LYN_SKILL_STATE_STANDARD:
		m_skillController->ChangeSkillSlotByAnimation(L"verticalCut_l0");
		m_skillController->ChangeSkillSlotByAnimation(L"slash1");
		m_skillController->ChangeSkillSlotByAnimation(L"frontDash");
		m_skillController->ChangeSkillSlotByAnimation(L"lowerSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"hold");
		m_skillController->ChangeSkillSlotByAnimation(L"rotateSoulBlade");
		m_skillController->ChangeSkillSlotByAnimation(L"lightningSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"thunderSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"chamWall");
	
		break;
	case LYN_SKILL_STATE_HIDE:
		m_skillController->ChangeSkillSlotByAnimation(L"baldo");
		m_skillController->ReleaseSkill(BNS_SKILL_SLOT_RB);
		m_skillController->ChangeSkillSlotByAnimation(L"frontDash");
		m_skillController->ChangeSkillSlotByAnimation(L"lowerSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"hold");
		m_skillController->ChangeSkillSlotByAnimation(L"rotateSoulBlade");
		m_skillController->ChangeSkillSlotByAnimation(L"lightningSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"thunderSlash");
		m_skillController->ChangeSkillSlotByAnimation(L"chamWall");

		break;
	case LYN_SKILL_STATE_AIR:
		break;
	case LYN_SKILL_STATE_MAGNETIC:
		break;

	default:
		break;
	}
	if (!GetTarget())
	{
		m_skillController->ChangeSkillSlot(L"frontKick");
	}
	else
	{
		if (GetDistanceToTarget() > 3)
		{
			m_skillController->ChangeSkillSlot(L"throwSoulBlade");
		}
		else
		{
			m_skillController->ChangeSkillSlot(L"frontKick");
		}
	}
}


void LynInfo::ResetBattleTimer()
{
	m_battleToPeaceTimer = BNS_BATTLE_TO_PEACE_TIME;
}

LYN_STATE LynInfo::GetState()
{
	return m_state;
}

void LynInfo::SetBattleState(BATTLE_STATE _state)
{
	m_battleState = _state;
}

BATTLE_STATE LynInfo::GetBattleState()
{
	return m_battleState;
}

void LynInfo::SetResistanceTimer(float _timer)
{
	if(m_resistanceTimer < _timer)
		m_resistanceTimer = _timer;
}

void LynInfo::SetResistance(bool _resistance)
{
	m_resistanceAlways = _resistance;
}

float LynInfo::GetDistanceToTarget()
{
	return m_distanceToTarget;
}

float LynInfo::GetEnergy()
{
	return m_energy;
}

void LynInfo::AddInnerPower(int _power)
{
	auto ui = UIManager::GetInstance();

	if (m_innerPower < 10)
	{
		if (m_innerPower + _power > 10)
		{
			_power = 10 - m_innerPower;
		}
		for (int i = 0; i < _power; ++i)
		{
			ui->AddInnerPower(m_innerPower + i);
		}
		m_innerPower += _power;
	}
	else
	{
		ui->FullInnerPower();
	}
}

void LynInfo::ReduceInnerPower(int _power)
{
	if (m_innerPower > 0)
	{
		auto ui = UIManager::GetInstance();
		if (m_innerPower - _power < 0)
		{
			_power = m_innerPower;
		}
		for (int i = 1; i <= _power; ++i)
		{
			ui->ReduceInnerPower(m_innerPower - i);
		}
		m_innerPower -= _power;
	}
}

UINT LynInfo::GetInnerPower()
{
	return m_innerPower;
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

GameObject * LynInfo::GetWeapon()
{
	return m_weapon;
}

Vector3 LynInfo::GetRightHandPosition()
{
	auto rightHandMat =  m_transform->GetWorldMatrix() * *m_matBattleStandard;
	Vector3 rightHandPos;
	memcpy(&rightHandPos, &rightHandMat._41, sizeof(Vector3));

	return rightHandPos;
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
	if (m_target != _obj)
	{
		UIManager::GetInstance()->UpdateTarget(_obj);
	}
	m_target = _obj;
	if (m_target)
	{
		m_distanceToTarget = Nalmak_Math::Distance(m_transform->GetWorldPosition(), _obj->GetTransform()->GetWorldPosition()) * BNS_DISTANCE_RATIO;
		UIManager::GetInstance()->UpdateTargetBoundaryBox(_obj);
	}
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

void LynInfo::MoveOn()
{
	m_isMovingBySkill = true;
}

void LynInfo::MoveOff()
{
	m_isMovingBySkill = false;
}

void LynInfo::SetSpeed(float _speed)
{
	m_targetSpeed = _speed;
}

const Vector3 & LynInfo::GetTargetInput()
{
	return m_targetInput;
}
