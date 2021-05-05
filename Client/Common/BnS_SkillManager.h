#pragma once


class BnS_SkillManager
{
	DECLARE_SINGLETON(BnS_SkillManager)
public:
	BnS_SkillManager();
	~BnS_SkillManager();
public:
	void CreateSkill();

private:
	vector<BnS_SkillInfo> m_skillInfo;
};

