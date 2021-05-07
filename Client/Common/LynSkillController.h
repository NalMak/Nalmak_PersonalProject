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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	//virtual void Release() override
	void ActiveSkill();
private:
	vector<BnS_Skill> m_skillInfo;
	LynInfo* m_info;
};

