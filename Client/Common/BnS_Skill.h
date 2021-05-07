#pragma once
class LynInfo;

class BnS_Skill
{
	friend class LynSkillController;
	using activationCondition = function<bool(LynInfo* _info)>;
public:
	BnS_Skill(const wstring& _stateName, BNS_SKILL_SLOT _skillSlot, const wstring& _skillIcon, float _coolTime, __int64 _actionKey,bool _isCombined, activationCondition _condition);
	~BnS_Skill();

public:
	bool CheckSkill(LynInfo* _info);
	BNS_SKILL_SLOT GetSkillSlot();
	Texture* GetSkillIconTex();
private:
	wstring m_stateName;
	Texture* m_skillIcon;
	BNS_SKILL_SLOT m_skillSlot;
	float m_coolTime;
	float m_remainTime;
	bool m_isCombined;
	__int64 m_actionKey;
	activationCondition m_activationCondition;
};

