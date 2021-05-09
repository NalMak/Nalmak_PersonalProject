#pragma once
class BnS_Skill;

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
	void SetSkillSlot(BnS_Skill* _skill);
	void UpdateSkillCoolTime(BNS_SKILL_SLOT _slot, float _ratio);
	void ChangeSkillSlot(BnS_Skill* _skill);
	void ReleaseSkillSlot(BNS_SKILL_SLOT _slot);
private:
	void SetDamageFont();
	void CreateSkillIcon(BNS_SKILL_SLOT _skillSlot, UINT _x, UINT _y);
private:
	GameObject* m_skillSlot[BNS_SKILL_SLOT::BNS_SKILL_SLOT_MAX];

	Texture* m_damageFont[10];
	Texture* m_criticalDamageFont[10];
};

