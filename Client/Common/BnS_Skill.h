#pragma once
#include "Component.h"
class BnS_SkillInfo;
class LynInfo;

using activationCondition = function<bool(LynInfo* _info)>;

class BnS_Skill :
	public Component
{
	friend class LynSkillController;

public:
	struct Desc
	{
	};
public:
	BnS_Skill(Desc* _desc);
	~BnS_Skill();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	void CreateSkill(const wstring& _stateName, BNS_SKILL_SLOT _skillSlot, const wstring& _skillIcon, float _coolTime, __int64 _actionKey, bool _isCombined, activationCondition _condition);
	bool IsAvailableSkill(LynInfo* _info);
	void ActiveSkill();

public:
	Texture* GetSkillIconTexture();
	BNS_SKILL_SLOT GetSkillSlotIndex();
	float GetCoolTime();
private:
	wstring m_stateName;
	bool m_isAvailable;
	Texture* m_skillIcon;
	BNS_SKILL_SLOT m_skillSlot;
	float m_coolTime;
	bool m_isCombined;
	__int64 m_actionKey;
	activationCondition m_activationCondition;
	bool m_available;
	float m_remainCoolTime;
};

