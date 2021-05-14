#include "stdafx.h"
#include "BnS_Buff.h"
#include "UIManager.h"
#include "LynInfo.h"
#include "BnS_Skill.h"
#include "BnS_SkillSlot.h"

BnS_Buff::BnS_Buff(Desc * _desc)
{
	m_buffTimer = _desc->buffTimer;
	m_timeRemaining = m_buffTimer;
	UIManager::GetInstance()->AddBuff(this,_desc->skill,_desc->key);
}

BnS_Buff::~BnS_Buff()
{
}

void BnS_Buff::Initialize()
{
	if (m_buffEvent)
	{
		(*m_buffEvent)(m_info);
	}
}

void BnS_Buff::Update()
{
	if (m_timeRemaining <= 0)
	{
		BuffOff();
		DESTROY(m_gameObject);
		return;
	}

	m_timeRemaining -= dTime;
	if (m_skillSlot)
	{
		m_skillSlot->SetCoolTimeRatio(m_timeRemaining / m_buffTimer);
	}
	if (m_buffEvent)
	{
		m_eventTimer += dTime;

		if (m_eventTimer > m_interval)
		{
			(*m_buffEvent)(m_info);
			m_eventTimer -= m_interval;
		}

	}
}

void BnS_Buff::Release()
{
	SAFE_DELETE(m_buffEvent);
}


void BnS_Buff::BuffOff()
{
	UIManager::GetInstance()->ReleaseBuff(this);
	m_skillSlot = nullptr;
}

void BnS_Buff::SetSkillSlot(BnS_SkillSlot * _slot)
{
	m_skillSlot = _slot;
}


void BnS_Buff::AddBuffEvent(BuffEvent _buff, float _interval, LynInfo* _lynInfo)
{
	m_buffEvent = new BuffEvent(_buff);
	m_interval = _interval;
	m_info = _lynInfo;

	m_eventTimer = 0.f;
}
