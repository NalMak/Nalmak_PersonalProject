#include "stdafx.h"
#include "BnS_SkillSlot.h"
#include "BnS_Skill.h"
BnS_SkillSlot::BnS_SkillSlot(Desc * _desc)
{
}

BnS_SkillSlot::~BnS_SkillSlot()
{
}

void BnS_SkillSlot::Initialize()
{
	m_material = GetComponent<CanvasRenderer>()->GetMaterial();
	m_coolTimeRatio = 0.f;
	m_skillChangeTimer = 0;

	m_material->SetFloat("g_changeRatio", 1);
}

void BnS_SkillSlot::Update()
{
	
}

void BnS_SkillSlot::EachRender()
{
	m_material->SetFloat("g_coolTimeAngle", m_coolTimeRatio * 360);

	if(m_preSkill)
		m_material->SetTexture("g_mainTex", m_preSkill->GetSkillIconTexture()->GetTexure(0));
	if(m_skill)
		m_material->SetTexture("g_nextTex", m_skill->GetSkillIconTexture()->GetTexure(0));

	if (m_skillChangeTimer > 0.f)
	{
		m_skillChangeTimer -= dTime;
		m_material->SetFloat("g_changeRatio", (BNS_SKILL_TEX_CHANGE_TIME - m_skillChangeTimer) / BNS_SKILL_TEX_CHANGE_TIME);
	}
}

void BnS_SkillSlot::SetSkill(BnS_Skill * _skill)
{
	m_skill = _skill;
	m_material->SetTexture("g_mainTex", m_skill->GetSkillIconTexture()->GetTexure(0));
}

void BnS_SkillSlot::ChangeSkill(BnS_Skill * _skill)
{
	if (!m_skill)
	{
		SetSkill(_skill);
		m_material->SetFloat("g_changeRatio",1);
		m_skillChangeTimer = 0;
		return;
	}
	
	m_preSkill = m_skill;
	m_skill = _skill;
	m_skillChangeTimer = BNS_SKILL_TEX_CHANGE_TIME;
}

void BnS_SkillSlot::SetCoolTimeRatio(float _ratio)
{
	m_coolTimeRatio = _ratio;
}
