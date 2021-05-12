#pragma once
class BnS_Skill;
class LynInfo;

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
	void SetLynInfo(LynInfo* _info);
	void UpdateEnergyUI(float _ratio);
	void UpdateHpUI(float _ratio);
	void UpdateTarget(GameObject* _target);
	void UpdateTargetBoundaryBox(GameObject* _target);


	void SetSkillSlot(BnS_Skill* _skill);
	void UpdateSkillCoolTime(BNS_SKILL_SLOT _slot, float _ratio);
	void ChangeSkillSlot(BnS_Skill* _skill);
	void ReleaseSkillSlot(BNS_SKILL_SLOT _slot);

	void AddInnerPower(UINT _index);
	void ReduceInnerPower(UINT _index);

private:
	void SetDamageFont();
	void CreateSkillIcon(BNS_SKILL_SLOT _skillSlot, UINT _x, UINT _y);
private:
	LynInfo* m_lynInfo;
	GameObject* m_skillSlot[BNS_SKILL_SLOT::BNS_SKILL_SLOT_MAX];
	CanvasRenderer* m_innerPowerIcon[10];
	GameObject* m_targetOutLine;
	
	Texture* m_damageFont[10];
	Texture* m_criticalDamageFont[10];
};

