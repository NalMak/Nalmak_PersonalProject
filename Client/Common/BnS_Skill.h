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
	void CreateSkill(const wstring& _stateName, const wstring& _skillName, BNS_SKILL_SLOT _skillSlot, const wstring& _skillIcon, float _coolTime, __int64 _actionKey,
		bool _isCombined, activationCondition _condition, bool _isRenderSlot, float _minDistance, float _maxDistance, UINT _innerForce);
	void UpdateAvailableSkill(LynInfo* _info);
	bool IsValidEvent(LynInfo* _info);
	bool GetAvailable(BNS_SKILL_CONDITION _condition);
	void ActiveSkill(LynInfo* _info);
	void RockSkill();
public:
	Texture* GetSkillIconTexture();
	BNS_SKILL_SLOT GetSkillSlotIndex();
	float GetCoolTime();
	int GetNeedInnerPower();
	const wstring& GetSkillName();
private:
	BitFlag<BNS_SKILL_CONDITION> m_useableCondition;
	BitFlag<BNS_SKILL_CONDITION> m_isUseable;


	

	bool m_isRenderSlot;
	wstring m_stateName;
	wstring m_skillName;
	Texture* m_skillIcon;
	BNS_SKILL_SLOT m_skillSlot;
	UINT  m_needInnerForce = 0;
	float m_minDistance = 0;
	float m_maxDistance = 0;
	float m_coolTime;
	bool m_isCombined;
	__int64 m_actionKey;
	activationCondition m_activationCondition;
	float m_remainCoolTime;
};

