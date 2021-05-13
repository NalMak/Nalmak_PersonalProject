#pragma once
#include "Component.h"
class BnS_Skill;

class BnS_SkillSlot :
	public Component
{
public:
	struct Desc
	{

	};
public:
	BnS_SkillSlot(Desc* _desc);
	~BnS_SkillSlot();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;
public:
	void SetSkill(BnS_Skill* _skill);
	void ChangeSkillTex(Texture* _tex);

	void SetCoolTimeRatio(float _ratio);
private:
	bool m_isChange;
	float m_coolTimeRatio;
	float m_skillChangeTimer;
	Texture* m_curSkill;
	Texture* m_nextSkill;

	Material* m_material;
};

