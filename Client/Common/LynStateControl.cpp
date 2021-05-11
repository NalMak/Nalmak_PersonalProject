#include "stdafx.h"
#include "LynStateControl.h"
#include "BnS_MainCamera.h"


LynStateControl::LynStateControl(Desc * _desc)
	:StateControl(&StateControl::Desc())
{
}

LynStateControl::~LynStateControl()
{
}

void LynStateControl::Initialize()
{
	m_character = GetComponent<CharacterController>();
	m_info = GetComponent<LynInfo>();
	m_animController_lower = GetComponents<AnimationController>()[0];
	m_animController_upper = GetComponents<AnimationController>()[1];
	auto cam = Core::GetInstance()->GetMainCamera()->GetComponent<BnS_MainCamera>();

	auto stateControls = GetComponents<LynStateControl>();
	for(auto& state : m_stateList)
	{
		LynState* lynState = (LynState*)(state.second);
		lynState->m_character = m_character;
		lynState->m_info = m_info;
		lynState->m_bnsMainCam = cam;
		if(lynState->m_isUpper)
			lynState->m_animController = m_animController_upper;
		else
			lynState->m_animController = m_animController_lower;
	}
	
	StateControl::Initialize();
}

void LynStateControl::Update()
{

	/*if (!m_character->IsGround())
	{
		if (!CompareState(L"jump"))
		{
			SetState(L"jump");
			return;
		}
	}*/
	DEBUG_LOG(L"Lyn Current State", GetCurStateString());
	StateControl::Update();
}

//void LynStateControl::SetSpeed(float _speed)
//{
//	m_targetSpeed = _speed;
//}
//
//void LynStateControl::UpdatePosition()
//{
//	m_info->UpdateWeapon();
//
//	UpdateDirection();
//
//	DEBUG_LOG(L"moveDir", m_dirState);
//
//	Vector3 velocity = { 0,0,0 };
//	velocity += m_inputDir.x * m_transform->GetRight() * m_targetSpeed;
//	velocity += m_inputDir.z * m_transform->GetForward() * m_targetSpeed;
//
//	m_character->SetVelocityX(velocity.x);
//	m_character->SetVelocityZ(velocity.z);
//}
//
//LYN_MOVE_DIR_STATE LynStateControl::UpdateDirection()
//{
//	m_targetInput = { 0,0,0 };
//	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
//	{
//		m_targetInput += {0, 0, 1};
//	}
//	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
//	{
//		m_targetInput -= {0, 0, 1};
//	}
//	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
//	{
//		m_targetInput -= {1, 0, 0};
//	}
//	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
//	{
//		m_targetInput += {1, 0, 0};
//	}
//	m_targetInput = Nalmak_Math::Normalize(m_targetInput);
//
//	m_inputDir = Nalmak_Math::Lerp(m_inputDir, m_targetInput, dTime * 10);
//
//	float shortLength = INFINITY;
//	int index = 0;
//	for (int i = 0; i < 9; ++i)
//	{
//		float length = Nalmak_Math::DistanceSq(m_directionState[i], m_inputDir);
//		if (length < shortLength)
//		{
//			index = i;
//			shortLength = length;
//		}
//	}
//	m_dirState = (LYN_MOVE_DIR_STATE)index;
//
//	return m_dirState;
//}
//
//LYN_MOVE_DIR_STATE LynStateControl::GetDirectionState()
//{
//	return m_dirState;
//}
