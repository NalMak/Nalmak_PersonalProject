#include "stdafx.h"
#include "LynState.h"


LynState::LynState()
{
}


LynState::~LynState()
{
}

void LynState::ReduceInnerPower(UINT _innerPower)
{
	if (m_isUpper)
		m_info->ReduceInnerPower(_innerPower);
}

void LynState::AddInnerPower(UINT _innerPower)
{
	if (m_isUpper)
		m_info->AddInnerPower(_innerPower);
}

void LynState::CreateAttackInfo(AttackInfo::Desc* _attackInfo, float _forward, float _height, float _powerMultiply)
{
	if (m_isUpper)
	{
		_attackInfo->host = m_gameObject;
		_attackInfo->power =(UINT)( m_info->m_power * _powerMultiply * Nalmak_Math::Rand(0.8f,1.2f));
		float critical =  Nalmak_Math::Rand(0.f, 1.f);
		_attackInfo->isCritical = m_info->m_criticalRatio < critical;
		INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
			->AddComponent<AttackInfo>(_attackInfo)
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * _forward + Vector3(0, _height, 0))
			->SetRotation(m_transform->GetWorldRotation());
	}
}

