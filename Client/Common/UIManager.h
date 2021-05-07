#pragma once
#include "BnS_Skill.h"

class UIManager
{
	DECLARE_SINGLETON(UIManager)
public:
	UIManager();
	~UIManager();
public:
	void CreateMainUI();
private:
	Material* m_hpBar;
	Material* m_energyBar;
	Material* m_enduranceBar;
public:
	void UpdateEnergyUI(float _ratio);
private:
	void SetDamageFont();
	void CreateSkillIcon(UINT _skillSlot, UINT _x, UINT _y);
	void ChangeSkillSlot(BnS_Skill& _skill);
private:
	GameObject* m_skillSlot[BNS_SKILL_SLOT::BNS_SKILL_SLOT_MAX];

	Texture* m_damageFont[10];
	Texture* m_criticalDamageFont[10];
};

