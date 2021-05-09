#include "stdafx.h"
#include "BnS_SkillSlot.h"

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
}

void BnS_SkillSlot::Update()
{
}

void BnS_SkillSlot::EachRender()
{
	m_material->SetFloat("g_coolTimeAngle", m_coolTimeRatio * 360);
}

void BnS_SkillSlot::SetSkill(BnS_Skill * _skill)
{
	m_skill = _skill;
}

void BnS_SkillSlot::ChangeSkill(BnS_Skill * _skill)
{
	m_skill = _skill;
}

void BnS_SkillSlot::SetCoolTimeRatio(float _ratio)
{
	m_coolTimeRatio = _ratio;
}
