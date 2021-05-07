#include "stdafx.h"
#include "BnS_Skill.h"




BnS_Skill::BnS_Skill(const wstring & _stateName, const wstring & _skillIcon, float _coolTime, __int64 _actionKey, bool _isCombined, activationCondition _condition)
{
	m_stateName = _stateName;
	m_isCombined = _isCombined;
	m_skillIcon = _skillIcon;
	m_coolTime = _coolTime;
	m_actionKey = _actionKey;
	m_activationCondition = _condition;
}

BnS_Skill::~BnS_Skill()
{
}

bool BnS_Skill::CheckSkill(LynInfo * _info)
{
	return m_activationCondition(_info);
}
