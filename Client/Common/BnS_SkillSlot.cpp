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
	m_isChange = false;
}

void BnS_SkillSlot::Update()
{
	
}

void BnS_SkillSlot::EachRender()
{
	if (!m_curSkill)
		return;



	if (!m_isChange)
	{
		m_material->SetFloat("g_changeRatio", 1);
		m_material->SetTexture("g_mainTex", m_curSkill->GetTexure(0));

	}
	else
	{
		if (m_skillChangeTimer > 0.f)
		{
			m_skillChangeTimer -= dTime;
			if (m_skillChangeTimer > 0)
			{
				m_material->SetTexture("g_mainTex", m_curSkill->GetTexure(0));
				m_material->SetTexture("g_nextTex", m_nextSkill->GetTexure(0));
				m_material->SetFloat("g_changeRatio", 1 - (BNS_SKILL_TEX_CHANGE_TIME - m_skillChangeTimer) / BNS_SKILL_TEX_CHANGE_TIME);
			}
			else
			{
				m_curSkill = m_nextSkill;
				m_material->SetTexture("g_mainTex", m_curSkill->GetTexure(0));
				m_material->SetFloat("g_changeRatio", 1);
				m_isChange = false;
			}
		}


	}

	
	m_material->SetFloat("g_coolTimeAngle", m_coolTimeRatio * 360);


}

void BnS_SkillSlot::SetSkill(BnS_Skill * _skill)
{
	m_curSkill = _skill->GetSkillIconTexture();
}

void BnS_SkillSlot::ChangeSkillTex(Texture * _tex)
{
	m_isChange = true;
	m_nextSkill = _tex;
	m_skillChangeTimer = BNS_SKILL_TEX_CHANGE_TIME;
}

void BnS_SkillSlot::SetCoolTimeRatio(float _ratio)
{
	m_coolTimeRatio = _ratio;
}
