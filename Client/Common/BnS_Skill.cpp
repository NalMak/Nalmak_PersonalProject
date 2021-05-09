#include "stdafx.h"
#include "BnS_Skill.h"
#include "LynInfo.h"

BnS_Skill::BnS_Skill(Desc * _desc)
{
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
}

void BnS_Skill::CreateSkill(const wstring& _stateName, BNS_SKILL_SLOT _skillSlot, const wstring & _skillIcon, float _coolTime, __int64 _actionKey, bool _isCombined, activationCondition _condition)
{
	m_stateName = _stateName;
	m_skillSlot = _skillSlot;
	m_isCombined = _isCombined;
	m_skillIcon = ResourceManager::GetInstance()->GetResource<Texture>(_skillIcon);
	m_coolTime = _coolTime;
	m_actionKey = _actionKey;
	m_activationCondition = _condition;
}

bool BnS_Skill::IsAvailableSkill(LynInfo* _info)
{
	return m_activationCondition(_info);
}

void BnS_Skill::ActiveSkill()
{
	m_remainCoolTime = m_coolTime;
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


