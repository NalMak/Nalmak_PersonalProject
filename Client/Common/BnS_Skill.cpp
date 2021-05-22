#include "stdafx.h"
#include "BnS_Skill.h"
#include "LynInfo.h"
#include "UIManager.h"

BnS_Skill::BnS_Skill(Desc * _desc)
{
	m_useableCondition.AllOff();
	m_useableCondition.On(BNS_SKILL_CONDITION_EVENT);
	m_isUseable.AllOn();
}

BnS_Skill::~BnS_Skill()
{
}

void BnS_Skill::Initialize()
{
	
}

void BnS_Skill::Update()
{
	if (m_remainCoolTime > 0)
	{
		m_remainCoolTime -= dTime;
	}
	else
	{
		m_remainCoolTime = 0;
	}
}

void BnS_Skill::CreateSkill(const wstring& _stateName,const wstring& _skillName, BNS_SKILL_SLOT _skillSlot, const wstring & _skillIcon, float _coolTime,
	__int64 _actionKey, bool _isCombined, activationCondition _condition, bool _isRenderSlot, float _minDistance, float _maxDistance, UINT _innerForce)
{
	m_stateName = _stateName;
	m_skillSlot = _skillSlot;
	m_isCombined = _isCombined;
	m_isRenderSlot = _isRenderSlot;
	m_skillName = _skillName;

	if (_minDistance != 0 || _maxDistance != 0)
	{
		m_minDistance = _minDistance;
		m_maxDistance = _maxDistance;
		m_useableCondition.On(BNS_SKILL_CONDITION_DISTANCE);
	}
	m_needInnerForce = _innerForce;
	if (_innerForce > 0)
	{
		m_useableCondition.On(BNS_SKILL_CONDITION_INNERFORCE);
	}
	m_skillIcon = ResourceManager::GetInstance()->GetResource<Texture>(_skillIcon);
	m_coolTime = _coolTime;
	m_actionKey = _actionKey; 
	m_activationCondition = _condition;
}

void BnS_Skill::UpdateAvailableSkill(LynInfo* _info)
{
	if (m_useableCondition.Check(BNS_SKILL_CONDITION_DISTANCE))
	{
		if (_info->GetTarget())
		{
			if (BETWEEN(_info->GetDistanceToTarget(), m_minDistance, m_maxDistance))
			{
				m_isUseable.On(BNS_SKILL_CONDITION_DISTANCE);
			}
			else
			{
				m_isUseable.Off(BNS_SKILL_CONDITION_DISTANCE);
			}
		}
		else
		{
			m_isUseable.Off(BNS_SKILL_CONDITION_DISTANCE);

		}
	}
 	if (m_useableCondition.Check(BNS_SKILL_CONDITION_INNERFORCE))
	{
		if (_info->GetInnerPower() >= (int)m_needInnerForce)
		{
			m_isUseable.On(BNS_SKILL_CONDITION_INNERFORCE);
		} 
		else
		{
			m_isUseable.Off(BNS_SKILL_CONDITION_INNERFORCE);
		}
	}

	if(m_isUseable.Check(BNS_SKILL_CONDITION_DISTANCE) && m_isUseable.Check(BNS_SKILL_CONDITION_INNERFORCE))
		UIManager::GetInstance()->SetSkillSlotColor(m_skillSlot, Vector4(1.f,1.f,1.f, 1));
	else
		UIManager::GetInstance()->SetSkillSlotColor(m_skillSlot, Vector4(0.2f, 0.2f, 0.2f, 1));

}

bool BnS_Skill::IsValidEvent(LynInfo * _info)
{
	return m_activationCondition(_info);
}

bool BnS_Skill::GetAvailable(BNS_SKILL_CONDITION _condition)
{
	return m_isUseable.Check(_condition);
}

void BnS_Skill::ActiveSkill(LynInfo* _info)
{
	m_remainCoolTime = m_coolTime;

	if(m_needInnerForce > 0)
		_info->ReduceInnerPower(m_needInnerForce);
}



Texture * BnS_Skill::GetSkillIconTexture()
{
	return m_skillIcon;
}

BNS_SKILL_SLOT BnS_Skill::GetSkillSlotIndex()
{
	return m_skillSlot;
}

float BnS_Skill::GetCoolTime()
{
	return m_remainCoolTime;
}

int BnS_Skill::GetNeedInnerPower()
{
	return m_needInnerForce;
}

const wstring & BnS_Skill::GetSkillName()
{
	return m_skillName;
}


