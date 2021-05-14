#pragma once
#include "Component.h"
#include "BnS_Skill.h"

class LynSkillController :
	public Component
{
public:
	struct Desc
	{

	};
public:
	LynSkillController(Desc* _desc);
	~LynSkillController();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	void UpdateSkill();
	void CreateSkill(const wstring& _stateName,
		BNS_SKILL_SLOT _skillSlot,
		const wstring & _skillIcon,
		float _coolTime,
		__int64 _actionKey,
		bool _isCombined,
		bool _isRenderSlot,
		float _minDistance,
		float _maxDistance, 
		UINT _innerForce,
		activationCondition _condition
		);
	void SetSkillSlot(const wstring& _name);
	void ChangeSkillSlot(const wstring& _name);
	void ChangeSkillSlotByAnimation(const wstring& _name);

	void ReleaseSkill(BNS_SKILL_SLOT _slot);
	//virtual void Release() override
	void ActiveSkill();
	BnS_Skill* GetSkill(const wstring& _skillName);
private:
	map<wstring, BnS_Skill*> m_allSkill;
	BnS_Skill* m_baseSkill[BNS_SKILL_SLOT::BNS_SKILL_SLOT_MAX];
	BnS_Skill* m_subSkill[10];
	AudioSource* m_audio;

	LynInfo* m_info;
};

