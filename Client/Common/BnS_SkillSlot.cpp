#include "stdafx.h"
#include "BnS_SkillSlot.h"
#include "BnS_Skill.h"
BnS_SkillSlot::BnS_SkillSlot(Desc * _desc)
	:SingleImage(&SingleImage::Desc())
{
	if (_desc->_skill)
	{
		SetSkill(_desc->_skill);
	}
}

BnS_SkillSlot::~BnS_SkillSlot()
{
}

void BnS_SkillSlot::Initialize()
{
	m_coolTimeRatio = 0.f;
	m_skillChangeTimer = 0;

	m_isChange = false;


	UIComponent::Initialize();
}

void BnS_SkillSlot::Update()
{
	
}


void BnS_SkillSlot::SetSkill(BnS_Skill * _skill)
{
	m_curSkill = _skill->GetSkillIconTexture();
	m_isChange = false;
}

void BnS_SkillSlot::SetSkill(Texture * _skill)
{
	m_curSkill = _skill;
}

void BnS_SkillSlot::ChangeSkillTex(Texture * _tex)
{
	m_isChange = true;
	m_nextSkill = _tex;
	m_skillChangeTimer = BNS_SKILL_TEX_CHANGE_TIME;
}

void BnS_SkillSlot::RockSkillSlot()
{
	m_coolTimeRatio = 1;
}

void BnS_SkillSlot::UnRockSkillSlot()
{
}


void BnS_SkillSlot::SetCoolTimeRatio(float _ratio)
{
	m_coolTimeRatio = 1 - _ratio;
}

void BnS_SkillSlot::Release()
{
	UIComponent::Release();
}

void BnS_SkillSlot::Render(Shader * _shader, Mesh * _mesh)
{
	if (!m_curSkill)
		return;

	if (!m_isChange)
	{
		_shader->SetFloat("g_changeRatio", 1);
		_shader->SetTexture("g_mainTex", m_curSkill->GetTexure(0));
	}
	else
	{
		if (m_skillChangeTimer > 0.f)
		{
			m_skillChangeTimer -= dTime;
			if (m_skillChangeTimer > 0)
			{
				_shader->SetTexture("g_mainTex", m_curSkill->GetTexure(0));
				_shader->SetTexture("g_nextTex", m_nextSkill->GetTexure(0));
				_shader->SetFloat("g_changeRatio", 1 - (BNS_SKILL_TEX_CHANGE_TIME - m_skillChangeTimer) / BNS_SKILL_TEX_CHANGE_TIME);
			}
			else
			{
				m_curSkill = m_nextSkill;
				_shader->SetTexture("g_mainTex", m_curSkill->GetTexure(0));
				_shader->SetFloat("g_changeRatio", 1);
				m_isChange = false;
			}
		}
	}
	_shader->SetVector("g_mainTexColor", m_color);
	_shader->SetFloat("g_coolTimeAngle", m_coolTimeRatio * 360);
	_shader->SetMatrix("g_world", m_transform->GetWorldUIMatrix());

	_shader->CommitChanges();
	_mesh->Draw();

}
