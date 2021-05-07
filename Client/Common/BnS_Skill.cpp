#include "stdafx.h"
#include "BnS_Skill.h"




BnS_Skill::BnS_Skill(const wstring & _stateName, BNS_SKILL_SLOT _skillSlot, const wstring & _skillIcon, float _coolTime, __int64 _actionKey, bool _isCombined, activationCondition _condition)
{
	m_stateName = _stateName;
	m_skillSlot = _skillSlot;
	m_isCombined = _isCombined;
	m_skillIcon = ResourceManager::GetInstance()->GetResource<Texture>(_skillIcon);
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

BNS_SKILL_SLOT BnS_Skill::GetSkillSlot()
{
	return m_skillSlot;
}

Texture * BnS_Skill::GetSkillIconTex()
{
	return m_skillIcon;
}
